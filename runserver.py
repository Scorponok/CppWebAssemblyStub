# If you don't want to use this script, the following command kinda works:
#   python -m SimpleHTTPServer 9090
# It will cause a "wasm streaming compile failed: TypeError: Response has unsupported MIME type" error to be reported
# when you load the page, but then the javascript that loads the WebAssembly will fall back to an alternate
# (presumably worse) way of loading it, which should still work.

import SimpleHTTPServer
import SocketServer

PORT = 9090

class Handler(SimpleHTTPServer.SimpleHTTPRequestHandler):
    pass

Handler.extensions_map['.wasm'] = 'application/wasm'

httpd = SocketServer.TCPServer(("", PORT), Handler)

print("serving at port", PORT)
httpd.serve_forever()
