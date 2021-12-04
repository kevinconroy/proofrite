libeps is a GPLed MIME library available from http://www.inter7.com/eps/
This is a small library and looks very portable. Certainly it works on
Linux and Darwin. There are other MIME libraries out there, but libeps
has the elegance of being a single dependency.

With respect to Multipart HTML, most documents use DOS-style \r\n line
endings and this confuses the current release of libeps (eps-1.2). The
patch in this directory (crlf.patch) should be applied to the eps-1.2
sources.

16th December, 2002
Francis James Franklin
