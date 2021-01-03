import socket
import os

os.system('rm -f decrypted*.bmp encrypted*.bin')

count = 1

while True:

   #opening a new socket for the client to connect
   s = socket.socket()
   s.bind(("localhost", 1500))
   print(f'Waiting for client to connect...')
   
   s.listen(1)
   c,a = s.accept()
   print(f'Client connected')

   #opening the file to be sent
   encrypt_filename = f'encrypted{count}.bin'
   filetodown = open(encrypt_filename, "wb")
   print(f'Downloading new file #{count}')

   while True:
      data = c.recv(1024)
   
#      if len(data) > 0:
#         print(data)
   
      # check if data ends with 'DONE'. if does, this is the last slice of the file
      if data[(len(data)-4):(len(data))] == b"DONE":
   
      # write the last data to the file
         if len(data) > 4:
            filetodown.write(data[0:(len(data)-4)])
   
         print("Done Receiving.")
         break

      filetodown.write(data)
   
   print(encrypt_filename+" received succesfully")
   
   #closing file, connection and socket
   filetodown.close() 
   c.shutdown(2)
   c.close()
   s.close()
   
   # now call rsa.exe to decrypt the received file
   decrypt_filename = encrypt_filename.replace("en","de").replace("bin", "bmp")
   
   command_line = f'.\\rsa.exe {encrypt_filename} {decrypt_filename}'
   # print(command_line)
   
   os.system(command_line)
   print(decrypt_filename+" decrypted succesfully\n")

   count += 1

#Done :)              # Close the connection