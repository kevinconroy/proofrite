/*
 * Copyright (C) 2002 Francis James Franklin <fjf@alinameridon.com>
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>

#include <ut_spi.h>

#include "Plugin.h"
#include "Document.h"

static ABI_Field_SPI FieldInterface = { ABI_FIELD_SPI_VERSION };

static int s_doc_init (void * plugin_data, void ** doc_data)
{
  Plugin * plugin = reinterpret_cast<Plugin *>(plugin_data);

  Document * doc = 0;
  try
    {
      doc = new Document(plugin);
    }
  catch (...)
    {
      doc = 0;
    }
  *doc_data = reinterpret_cast<void *>(doc);

  if (doc == 0) return ABI_SPI_ERROR;

  // TODO

  return !ABI_SPI_ERROR;
}

static int s_doc_free (void * plugin_data, void * doc_data)
{
  Plugin * plugin = reinterpret_cast<Plugin *>(plugin_data);

  Document * doc = reinterpret_cast<Document *>(doc_data);

  if (doc) delete doc;

  return !ABI_SPI_ERROR;
}

static int s_doc_fins (void * /*plugin_data*/, void * doc_data, char *** field_atts)
{
  Document * doc = reinterpret_cast<Document *>(doc_data);

  return doc->fins (field_atts) ? (!ABI_SPI_ERROR) : ABI_SPI_ERROR;
}

static int s_doc_fdel (void * /*plugin_data*/, void * doc_data, char *** field_atts)
{
  Document * doc = reinterpret_cast<Document *>(doc_data);

  return doc->fdel (field_atts) ? (!ABI_SPI_ERROR) : ABI_SPI_ERROR;
}

static int s_doc_fref (void * /*plugin_data*/, void * doc_data, char *** field_atts,
		       char ** content_type, char ** utf8_text)
{
  Document * doc = reinterpret_cast<Document *>(doc_data);

  return doc->fref (field_atts, content_type, utf8_text) ? (!ABI_SPI_ERROR) : ABI_SPI_ERROR;
}

// static char * s_dependencies[] = { "this", "that", "the other", 0 };
static char * s_name = "abi-spi-referee-1";

extern "C" ABI_SPI_EXPORT
int abi_spi_version (int version, char ** name, char *** /* dependencies */)
{
  // *dependencies = s_dependencies;
  *name = s_name;
  if (version < ABI_SPI_VERSION) return ABI_SPI_ERROR; // don't bother supporting old versions
  return ABI_SPI_VERSION;
}

extern "C" ABI_SPI_EXPORT
int abi_spi_register (ABI_SPI * spi, struct ABI_Foreign_SPI * const * /* spies */)
{
  if (spi->version != ABI_SPI_VERSION) return ABI_SPI_VERSION;

  static bool registered = false;
  if (registered) return ABI_SPI_ERROR;
  registered = true;

  Plugin * plugin = 0;
  try
    {
      plugin = new Plugin;
    }
  catch (...)
    {
      plugin = 0;
    }
  spi->plugin_data = reinterpret_cast<void *>(plugin);

  if (plugin == 0) return ABI_SPI_ERROR;

  spi->plugin_name    = "AbiReferee";
  spi->plugin_desc    = "SPI Field Test";
  spi->plugin_version = "0.0.1";
  spi->plugin_author  = "Francis James Franklin <fjf@alinameridon.com>";
  spi->plugin_usage   = "None that I know of - at least, none yet...";

  FieldInterface.doc_init = s_doc_init;
  FieldInterface.doc_free = s_doc_free;
  FieldInterface.doc_fins = s_doc_fins;
  FieldInterface.doc_fdel = s_doc_fdel;
  FieldInterface.doc_fref = s_doc_fref;

  spi->spi_field = &FieldInterface;

  return ABI_SPI_VERSION;
}

extern "C" ABI_SPI_EXPORT
int abi_spi_unregister (void * plugin_data, ABI_SPI * spi)
{
  Plugin * plugin = reinterpret_cast<Plugin *>(plugin_data);

  if (plugin) delete plugin;

  return 0; // return value is ignored
}
