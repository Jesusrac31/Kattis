import subprocess
import time
import shutil
from colorama import init
from colorama import Fore

name_input = "input"
name_output = "output"
file_dir = '"Problemas/Progress/Gold Leaf/Gold-Leaf.cpp"'

command1 = 'g++ -o main.exe '+file_dir
subprocess.run(command1)

init(autoreset=True) 

for i in range(1,73):
    
    # Ruta del archivo de origen
    archivo_origen = "Tester/Input/"+name_input+".in"+str(i)

    # Ruta del archivo de destino
    archivo_destino = "input.in"

    try:
        shutil.copyfile(archivo_origen, archivo_destino)
        print(f"El archivo '{archivo_origen}' se copió a '{archivo_destino}' correctamente.")
    except FileNotFoundError:
        print(f"El archivo '{archivo_origen}' no fue encontrado.")
    except Exception as e:
        print(f"Ocurrió un error: {e}")

    
    ruta_exe = "main.exe"

    # Archivo de entrada
    archivo_entrada = "input.in"

    # Archivo de salida
    archivo_salida = "output.txt"

    # Abre el archivo de entrada en modo lectura
    with open(archivo_entrada, "r") as input_file:
        # Lee el contenido del archivo de entrada
        entrada = input_file.read()

    # Abre el archivo de salida en modo escritura
    with open(archivo_salida, "w",  encoding="utf-8") as output_file:
        try:
            # Ejecuta el programa .exe
            resultado = subprocess.run(ruta_exe, input=entrada, capture_output=True, text=True, check=True)

            # Imprime la salida del programa en el archivo de salida
            output_file.write(str(resultado.stdout))

            # Imprime la salida del programa en la consola
            #print("Salida del programa:")
            #print(resultado.stdout)

        except subprocess.CalledProcessError as e:
            # Maneja errores
            print(f"Error al ejecutar el programa: {e}")
            output_file.write(f"Error: {e}")

    with open("Tester/Output/"+name_output+".out"+str(i), "r") as solFile:
        sol = solFile.read()
    
    if (sol.strip() == (resultado.stdout).strip()):
        print(Fore.GREEN + f"Test {i} correcto")
    else:
        print(Fore.RED + f"Test {i} incorrecto ")
        print("Expected: " + sol)
        print("Got: " + resultado.stdout)

        input("Presiona cualquier tecla para continuar")