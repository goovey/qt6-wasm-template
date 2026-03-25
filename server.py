import http.server
import socketserver

PORT = 3100

class WasmHandler(http.server.SimpleHTTPRequestHandler):
    def end_headers(self):
        # Mandatory security headers for WebAssembly
        self.send_header("Cross-Origin-Opener-Policy", "same-origin")
        self.send_header("Cross-Origin-Embedder-Policy", "require-corp")
        # Ensure correct MIME type
        if self.path.endswith(".wasm"):
            self.send_header("Content-Type", "application/wasm")
        super().end_headers()

print(f"Serving at http://localhost:{PORT}")
with socketserver.TCPServer(("", PORT), WasmHandler) as httpd:
    httpd.serve_forever()
