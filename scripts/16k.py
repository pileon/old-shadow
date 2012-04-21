#!/usr/bin/env python

# Version: 1.05

import cgi, os, sys, string, re

quiet = 0

def stats(line):
  if not quiet:
    print line

def showForm():
  print """
<HTML><BODY>
<FORM METHOD="post" ENCTYPE="multipart/form-data">
Select options that fit your language below:"""
  for opt,optname in options.items():
    print "<BR><INPUT TYPE=checkbox NAME=%s> %s\n" % (opt, optname)

  print """
<BR>
Enter filename to upload: <INPUT TYPE=file NAME=file>
<BR>
<INPUT TYPE=submit NAME=submit VALUE="Process file">
</FORM>
</BODY></HTML>
"""

def handleInput(form):
  file = form["file"]
  if not file.file:
    raise Exception, "Not a file"
  data = file.value
  print "<PRE>\n"
  analyzeFile(data, form)
  print "</PRE>\n"


def analyzeFile(data, opt):
  global quiet
  
  if opt.has_key('q'):
    quiet = 1
  
  stats("File size:                   %6d bytes" % len(data))
  stats("Lines:                       %6d" % string.count(data, '\n'))

  data = string.replace(data, '\r', '')
  stats("\\r stripped:                 %6d" % len(data))

  if opt.has_key('h'):
    data = re.compile('#.*$', re.MULTILINE).sub('',data)
    stats("# removed:                   %6d" % len(data))

  if opt.has_key('a'):
    data = re.compile('\'.*$', re.MULTILINE).sub('',data)
    stats("' removed:                   %6d" % len(data))

  if opt.has_key('e'):
    data = re.compile(';.*$', re.MULTILINE).sub('',data)
    stats("; removed:                   %6d" % len(data))

  if opt.has_key('s'):
    data = re.compile('//.*$', re.MULTILINE).sub('',data)
    stats("// removed:                  %6d" % len(data))

  if opt.has_key('c'):
    data = re.compile(r'/\*.*?\*/',re.DOTALL).sub('',data)
    stats("/* removed:                  %6d" % len(data))

  if opt.has_key('l'):
    data = re.compile('^[ \t]+', re.MULTILINE).sub('',data)
    data = re.compile('[ \t]+', re.MULTILINE).sub(' ',data)
    stats("leading blanks removed:      %6d" % len(data))

  if opt.has_key('b'):
    data = re.compile(r'^\s*\n', re.MULTILINE).sub('',data)
    data = re.compile('[ \t]+$', re.MULTILINE).sub('',data)
    stats("blank lines stripped:        %6d" % len(data))

  if opt.has_key('d'):
    data = re.compile('--.*$', re.MULTILINE).sub('',data)
    stats("-- removed:                  %6d" % len(data))

  if opt.has_key('p'):
    # assumes xemacs mode; 4 spaces -> 1 tab
    for i in xrange(10):
      data = re.compile('^' + ('    ' * (10-i)), re.MULTILINE).sub('\t' * (10-i), data)
    stats("spaces to tabs:              %6d" % len(data))

    # Can strip duplicate blanks so long as they're not at the start of the
    # line
    data = re.compile(r'(\S+)[ \t]+', re.MULTILINE).sub(r'\1 ', data)
    stats("duplicate blanks stripped:   %6d" % len(data))

  stats("\nFinal result:                %6d" % len(data))
  stats("                             ======\n")

  if len(data) > 16384:
    stats("You are OVER the limit!")
  else:
    stats("Size is acceptable.")

  stats("\nModified file follows")
  stats("=====================")
  if os.environ.has_key('REQUEST_METHOD'):
    print cgi.escape(data)
  else:
    print data

options = {
  'h': "Strip everything after # (Python, Perl)",
  's': "Skip everything after // (C++, Java)",
  'c': "Skip everything between /* */ (C, Java, C++)",
  'l': "Skip leading blanks, compress multiple blanks (everything but Python)",
  'b': "Strip any fully blank lines and trailing blanks (all languages)",
  'a': "Strip everything after ' (Visual Basic)",
  'e': "Strip everything after ; (REBOL)",
  'd': "Skip everything after -- (ADA, SQL)",
  'p': "Convert leading spaces to tabs (4 spaces per tab) then compress non-leading blanks (Python)",
  'q': "Only produce modified file, no stats"
}

def handleCommandLine():
  opt = {}
  data = ""
  
  for arg in sys.argv[1:]:
    if arg[0] == '-':
      if not options.has_key(arg[1]):
        print "Unknown option: %c" % arg[1]
        sys.exit(1)
      opt[arg[1]] = 1
    else: # must be a file
      try:
        data = data + open(arg).read()
      except:
        print "Error reading file %s" % arg

  if not data:
    print "No input files specified. Following are valid options:"
    for opt,desc in options.items():
      print "-%c: %s" % (opt,desc)
    print "\nFor example:\n%s -l -c -b file1.c file2.c (for C programs)" % sys.argv[0]
    print "%s -h -b -p file.py (for Python)"  % sys.argv[0]
  else:
    analyzeFile(data, opt)
  
# Called as CGI or command line?
if not os.environ.has_key('REQUEST_METHOD'):
  handleCommandLine()
else:
  print "Content-type: text/html\n"
  sys.stderr = sys.stdout
  form = cgi.FieldStorage()
  if form.has_key('submit'):
    handleInput(form)
  else:
    showForm()

