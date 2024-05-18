import ctypes
import sys
import os

args = sys.argv[1:]
if os.name == 'nt':
    library_path = args[0] + '/HelloJNI.dll'
else:
    library_path = args[0] + '/libHelloJNI.so' 

# Charger la DLL
sl = ctypes.CDLL(library_path)

# Définir le prototype de la fonction Java_HelloJNI_sayHello
sl.Java_HelloJNI_sayHello.restype = None  # La fonction ne retourne rien

# Appeler la fonction doSomething
sl.Java_HelloJNI_sayHello()

