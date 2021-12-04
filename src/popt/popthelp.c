/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 4 -*- */

/** \ingroup popt
 * \file popt/popthelp.c
 */

/* (C) 1998-2000 Red Hat, Inc. -- Licensing details are in the COPYING
   file accompanying popt source distributions, available from 
   ftp://ftp.rpm.org/pub/rpm/dist. */

#include "system.h"
#include "poptint.h"

static void displayArgs(poptContext con,
		/*@unused@*/ enum poptCallbackReason foo,
		struct poptOption * key, 
		/*@unused@*/ const char * arg, /*@unused@*/ void * data)
{
    if (key->shortName == '?')
	poptPrintHelp(con, stdout, 0);
    else
	poptPrintUsage(con, stdout, 0);
    exit(0);
}

struct poptOption poptHelpOptions[] = {
    { NULL, '\0', POPT_ARG_CALLBACK, (void *)&displayArgs, '\0', NULL, NULL },
    { "help", '?', 0, NULL, '?', N_("Show this help message"), NULL },
    { "usage", '\0', 0, NULL, 'u', N_("Display brief usage message"), NULL },
    POPT_TABLEEND
} ;


#ifdef _WIN32  
    /* Define MSGPOPUP to enable concatenating all the
     * message lines into msgHelp, such as for displaying
     * in a MessageBox or other popup dialog.
     * Otherwise MSGPOPUP should be undefined.
     */
    #define MSGPOPUP
#endif

#ifdef MSGPOPUP
    /* TODO: fix me so as not to use hardcoded limits
     * All fprintfs are duplicated and appended via sprintfs
     * to this static buffer, it is presently assumed that
     * there is no need to reset this (mhp = msgHelp)
     * Warning: possibility of buffer overflow issues!
     */
    char msgHelp[8192] = "";
    char *mhp = msgHelp;
#endif


/*@observer@*/ /*@null@*/ static const char *const
getTableTranslationDomain(const struct poptOption *table)
{
  const struct poptOption *opt;

  for(opt = table;
      opt->longName || opt->shortName || opt->arg;
      opt++) {
    if(opt->argInfo == POPT_ARG_INTL_DOMAIN)
      return opt->arg;
  }

  return NULL;
}

/*@observer@*/ /*@null@*/ static const char *const
getArgDescrip(const struct poptOption * opt, const char *translation_domain)
{
    if (!(opt->argInfo & POPT_ARG_MASK)) return NULL;

    if (opt == (poptHelpOptions + 1) || opt == (poptHelpOptions + 2))
	if (opt->argDescrip) return POPT_(opt->argDescrip);

    if (opt->argDescrip) return D_(translation_domain, opt->argDescrip);

    switch (opt->argInfo & POPT_ARG_MASK) {
    case POPT_ARG_NONE:		return POPT_("NONE");
    case POPT_ARG_VAL:		return POPT_("VAL");
    case POPT_ARG_INT:		return POPT_("INT");
    case POPT_ARG_LONG:		return POPT_("LONG");
    case POPT_ARG_STRING:	return POPT_("STRING");
    case POPT_ARG_FLOAT:	return POPT_("FLOAT");
    case POPT_ARG_DOUBLE:	return POPT_("DOUBLE");
    default:			return POPT_("ARG");
    }
}

static void singleOptionHelp(FILE * f, int maxLeftCol, 
			     const struct poptOption * opt,
			     const char *translation_domain)
{
    int indentLength = maxLeftCol + 5;
    int lineLength = 79 - indentLength;
    const char * help = D_(translation_domain, opt->descrip);
    const char * argDescrip = getArgDescrip(opt, translation_domain);
    int helpLength;
    char * left;
    int nb = maxLeftCol + 1;

    /* Make sure there's more than enough room in target buffer. */
    if (opt->longName)	nb += strlen(opt->longName);
    if (argDescrip)	nb += strlen(argDescrip);

    left = malloc(nb);
    left[0] = left[maxLeftCol] = '\0';

    if (opt->longName && opt->shortName)
	sprintf(left, "-%c, %s%s", opt->shortName,
		((opt->argInfo & POPT_ARGFLAG_ONEDASH) ? "-" : "--"),
		opt->longName);
    else if (opt->shortName) 
	sprintf(left, "-%c", opt->shortName);
    else if (opt->longName)
	sprintf(left, "%s%s",
		((opt->argInfo & POPT_ARGFLAG_ONEDASH) ? "-" : "--"),
		opt->longName);
    if (!*left) goto out;
    if (argDescrip) {
	char * le = left + strlen(left);
	if (opt->argInfo & POPT_ARGFLAG_OPTIONAL)
	    *le++ = '[';
	if (opt->argDescrip == NULL) {
	    switch (opt->argInfo & POPT_ARG_MASK) {
	    case POPT_ARG_NONE:
		sprintf(le, "[true]");
		break;
	    case POPT_ARG_VAL:
	    {   long aLong = opt->val;

		if (opt->argInfo & POPT_ARGFLAG_NOT) aLong = ~aLong;
		switch (opt->argInfo & POPT_ARGFLAG_LOGICALOPS) {
		case POPT_ARGFLAG_OR:
		    sprintf(le, "[|=0x%lx]", aLong);	break;
		case POPT_ARGFLAG_AND:
		    sprintf(le, "[&=0x%lx]", aLong);	break;
		case POPT_ARGFLAG_XOR:
		    sprintf(le, "[^=0x%lx]", aLong);	break;
		default:
		    if (!(aLong == 0L || aLong == 1L || aLong == -1L))
			sprintf(le, "[=%ld]", aLong);
		    break;
		}
	    }	break;
	    case POPT_ARG_INT:
	    case POPT_ARG_LONG:
	    case POPT_ARG_STRING:
	    case POPT_ARG_FLOAT:
	    case POPT_ARG_DOUBLE:
		sprintf(le, "=%s", argDescrip);
		break;
	    }
	} else {
	    sprintf(le, "=%s", argDescrip);
	}
	le += strlen(le);
	if (opt->argInfo & POPT_ARGFLAG_OPTIONAL)
	    *le++ = ']';
	*le = '\0';
    }

    if (help) {
	fprintf(f,"  %-*s   ", maxLeftCol, left);
#ifdef MSGPOPUP
	sprintf(mhp,"  %-*s   ", maxLeftCol, left);  mhp+=strlen(mhp);
#endif
    }
    else {
	fprintf(f,"  %s\n", left); 
#ifdef MSGPOPUP
	sprintf(mhp,"  %s\n", left);  mhp+=strlen(mhp);
#endif
	goto out;
    }

    helpLength = strlen(help);
    while (helpLength > lineLength) {
	const char * ch;
	char format[10];

	ch = help + lineLength - 1;
	while (ch > help && !isspace(*ch)) ch--;
	if (ch == help) break;		/* give up */
	while (ch > (help + 1) && isspace(*ch)) ch--;
	ch++;

	sprintf(format, "%%.%ds\n%%%ds", (int) (ch - help), indentLength);
	fprintf(f, format, help, " ");
#ifdef MSGPOPUP
	sprintf(mhp, format, help, " ");  mhp+=strlen(mhp);
#endif
	help = ch;
	while (isspace(*help) && *help) help++;
	helpLength = strlen(help);
    }

    if (helpLength) {
	fprintf(f, "%s\n", help);
#ifdef MSGPOPUP
	sprintf(mhp, "%s\n", help);  mhp+=strlen(mhp);
#endif
    }

out:
    free(left);
}

static int maxArgWidth(const struct poptOption * opt,
		       const char * translation_domain)
{
    int max = 0;
    int this;
    const char * s;
    
    while (opt->longName || opt->shortName || opt->arg) {
	if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE) {
	    this = maxArgWidth(opt->arg, translation_domain);
	    if (this > max) max = this;
	} else if (!(opt->argInfo & POPT_ARGFLAG_DOC_HIDDEN)) {
	    this = sizeof("  ")-1;
	    if (opt->shortName) this += sizeof("-X")-1;
	    if (opt->shortName && opt->longName) this += sizeof(", ")-1;
	    if (opt->longName) {
		this += ((opt->argInfo & POPT_ARGFLAG_ONEDASH)
			? sizeof("-")-1 : sizeof("--")-1);
		this += strlen(opt->longName);
	    }

	    s = getArgDescrip(opt, translation_domain);
	    if (s)
		this += sizeof("=")-1 + strlen(s);
	    if (opt->argInfo & POPT_ARGFLAG_OPTIONAL) this += sizeof("[]")-1;
	    if (this > max) max = this;
	}

	opt++;
    }
    
    return max;
}

static void singleTableHelp(FILE * f, const struct poptOption * table, 
			    int left,
			    const char *translation_domain)
{
    const struct poptOption * opt;
    const char *sub_transdom;

    for (opt = table; (opt->longName || opt->shortName || opt->arg); opt++) {
	if ((opt->longName || opt->shortName) && 
	    !(opt->argInfo & POPT_ARGFLAG_DOC_HIDDEN))
	    singleOptionHelp(f, left, opt, translation_domain);
    }

    for (opt = table; (opt->longName || opt->shortName || opt->arg); opt++) {
	if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE) {
	    sub_transdom = getTableTranslationDomain(opt->arg);
	    if(!sub_transdom)
		sub_transdom = translation_domain;
	    
	    if (opt->descrip)
	    {
		fprintf(f, "\n%s\n", D_(sub_transdom, opt->descrip));
#ifdef MSGPOPUP
	      sprintf(mhp, "\n%s\n", D_(sub_transdom, opt->descrip));  mhp+=strlen(mhp);
#endif
	    }

	    singleTableHelp(f, opt->arg, left, sub_transdom);
	}
    }
}

static int showHelpIntro(poptContext con, FILE * f)
{
    int len = 6;
    const char * fn;

    fprintf(f, POPT_("Usage:"));
#ifdef MSGPOPUP
    sprintf(mhp, POPT_("Usage:"));  mhp+=strlen(mhp);
#endif
    if (!(con->flags & POPT_CONTEXT_KEEP_FIRST)) {
	fn = con->optionStack->argv[0];
	if (strchr(fn, '/')) fn = strrchr(fn, '/') + 1;
	fprintf(f, " %s", fn);
#ifdef MSGPOPUP
	sprintf(mhp, " %s", fn);  mhp+=strlen(mhp);
#endif
	len += strlen(fn) + 1;
    }

    return len;
}

void poptPrintHelp(poptContext con, FILE * f, /*@unused@*/ int flags)
{
    int leftColWidth;

    showHelpIntro(con, f);
    if (con->otherHelp)
    {
	fprintf(f, " %s\n", con->otherHelp);
#ifdef MSGPOPUP
	sprintf(mhp, " %s\n", con->otherHelp);  mhp+=strlen(mhp);
#endif
    }
    else
    {
	fprintf(f, " %s\n", POPT_("[OPTION...]"));
#ifdef MSGPOPUP
	sprintf(mhp, " %s\n", POPT_("[OPTION...]"));  mhp+=strlen(mhp);
#endif
    }

    leftColWidth = maxArgWidth(con->options, NULL);
    singleTableHelp(f, con->options, leftColWidth, NULL);

    #if defined(_WIN32) && defined(MSGPOPUP)
    /* TODO: change to a custom dialog that uses a fixed with font for text! */
    MessageBox(NULL, msgHelp, "Command Line Option Help", MB_OK|MB_ICONINFORMATION);
    #endif
}

static int singleOptionUsage(FILE * f, int cursor, 
			     const struct poptOption * opt,
			     const char *translation_domain)
{
    int len = 3;
    char shortStr[2] = { '\0', '\0' };
    const char * item = shortStr;
    const char * argDescrip = getArgDescrip(opt, translation_domain);

    if (opt->shortName) {
	if (!(opt->argInfo & POPT_ARG_MASK)) 
	    return cursor;	/* we did these already */
	len++;
	shortStr[0] = opt->shortName;
	shortStr[1] = '\0';
    } else if (opt->longName) {
	len += 1 + strlen(opt->longName);
	item = opt->longName;
    }

    if (len == 3) return cursor;

    if (argDescrip) 
	len += strlen(argDescrip) + 1;

    if ((cursor + len) > 79) {
	fprintf(f, "\n       ");
#ifdef MSGPOPUP
	sprintf(mhp, "\n       ");  mhp+=strlen(mhp);
#endif
	cursor = 7;
    } 

    fprintf(f, " [-%s%s%s%s]",
	((opt->shortName || (opt->argInfo & POPT_ARGFLAG_ONEDASH)) ? "" : "-"),
	item,
	(argDescrip ? (opt->shortName ? " " : "=") : ""),
	(argDescrip ? argDescrip : ""));
#ifdef MSGPOPUP
    sprintf(mhp, " [-%s%s%s%s]",
	((opt->shortName || (opt->argInfo & POPT_ARGFLAG_ONEDASH)) ? "" : "-"),
	item,
	(argDescrip ? (opt->shortName ? " " : "=") : ""),
	(argDescrip ? argDescrip : ""));  mhp+=strlen(mhp);
#endif

    return cursor + len + 1;
}

static int singleTableUsage(FILE * f, int cursor,
	const struct poptOption * opt, const char * translation_domain)
{
    for (; (opt->longName || opt->shortName || opt->arg) ; opt++) {
        if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INTL_DOMAIN)
	    translation_domain = (const char *)opt->arg;
	else if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE) 
	    cursor = singleTableUsage(f, cursor, opt->arg, translation_domain);
	else if ((opt->longName || opt->shortName) && 
		 !(opt->argInfo & POPT_ARGFLAG_DOC_HIDDEN))
	    cursor = singleOptionUsage(f, cursor, opt, translation_domain);
    }

    return cursor;
}

static int showShortOptions(const struct poptOption * opt, FILE * f, char * str)
{
    char s[300];		/* this is larger then the ascii set, so
				   it should do just fine */

    s[0] = '\0';
    if (str == NULL) {
	memset(s, 0, sizeof(s));
	str = s;
    }

    for (; (opt->longName || opt->shortName || opt->arg); opt++) {
	if (opt->shortName && !(opt->argInfo & POPT_ARG_MASK))
	    str[strlen(str)] = opt->shortName;
	else if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_INCLUDE_TABLE)
	    showShortOptions(opt->arg, f, str);
    } 

    if (s != str || !*s)
	return 0;

    fprintf(f, " [-%s]", s);
#ifdef MSGPOPUP
    sprintf(mhp, " [-%s]", s);  mhp+=strlen(mhp);
#endif
    return strlen(s) + 4;
}

void poptPrintUsage(poptContext con, FILE * f, /*@unused@*/ int flags)
{
    int cursor;

    cursor = showHelpIntro(con, f);
    cursor += showShortOptions(con->options, f, NULL);
    singleTableUsage(f, cursor, con->options, NULL);

    if (con->otherHelp) {
	cursor += strlen(con->otherHelp) + 1;
	if (cursor > 79) {
	  fprintf(f, "\n       ");
#ifdef MSGPOPUP
	  sprintf(mhp, "\n       ");  mhp+=strlen(mhp);
#endif
	}
	fprintf(f, " %s", con->otherHelp);
#ifdef MSGPOPUP
	sprintf(mhp, " %s", con->otherHelp);  mhp+=strlen(mhp);
#endif
    }

    fprintf(f, "\n");
#ifdef MSGPOPUP
    sprintf(mhp, "\n");  mhp+=strlen(mhp);
#endif
}

void poptSetOtherOptionHelp(poptContext con, const char * text) {
    if (con->otherHelp) free((void *)con->otherHelp);
    con->otherHelp = xstrdup(text);
}
