from pythonosc import dispatcher, osc_server, udp_client

# Cliente para enviar feedback a la app (puerto 7001)
fb = udp_client.SimpleUDPClient("127.0.0.1", 7001)

def handle(addr, val):
    print(addr, val)
    # Envía feedback sencillo (mismo valor de vuelta)
    v = max(0.0, min(1.0, float(val)))
    fb.send_message("/feedback", v)

disp = dispatcher.Dispatcher()
disp.map("/slider/*", handle)

print("Listening on 127.0.0.1:7000  ;  feedback -> 7001")
osc_server.ThreadingOSCUDPServer(("127.0.0.1", 7000), disp).serve_forever()
