

import os




import tornado.ioloop
import tornado.web
from tornado.httpserver import HTTPServer

HOST = 'localhost'
PORT = 8880

import json
import time
import requests
import datetime
import dateutil

from collections import defaultdict

import numpy as np

import matplotlib.pyplot as plt
#from mpld3 import fig_to_html, fig_to_d3, show_d3

class plot_figure(tornado.web.RequestHandler):
    def get(self, *args):
        self.post(*args)
        #self.write("not implemented yet")

    def post(self, *args):
        """ 
        
        """
        
        
        os.system('./graphgen '+str(8))

        self.write('<!DOCTYPE html><html><body>')
        self.write('<img src=\"./deneme_orig.png\">')
        self.write('</body></html>')

        #self.add_header('Content-Type', 'application/json')


DEBUG = True
DIRNAME = os.path.dirname(__file__)
STATIC_PATH = os.path.join(DIRNAME, '.')


routes_config = [
    (r"/plot_figure", plot_figure),
    (r"/(.*\.png)", tornado.web.StaticFileHandler,{"path": "." }),
#    (r"/set_params", set_params),
]

#    (r"/deneme.png", tornado.web.StaticFileHandler, {"path": "."},),

application = tornado.web.Application(routes_config)

def start():
    print "GraphGen Server Starting on port %s" % PORT
    http_server = HTTPServer(application, xheaders=True)
    http_server.listen(PORT)
    tornado.ioloop.IOLoop.instance().start()
    return application

if __name__ == "__main__":
    start()
