from pythonosc import dispatcher, osc_server

def handle(addr, val):
    print(addr, val)

disp = dispatcher.Dispatcher()
disp.map("/slider/*", handle)

print("Listening on 127.0.0.1:7000")
osc_server.ThreadingOSCUDPServer(("127.0.0.1", 7000), disp).serve_forever()
