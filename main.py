# Project: AES
# Author: Guillaume Noël
# Date: 2023-31-05
# Description: This file is used to test the encryption and decryption of the AES algorithm



from cryptography.fernet import Fernet
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
import os
from cryptography.hazmat.primitives.padding import PKCS7
import datetime
import hashlib

def getIv():
    now = datetime.datetime.now()
    date_str = now.strftime("%y-%m-%d%H:%M:%S")
    date_bytes = date_str.encode('utf-8')
    return date_bytes
def encrypt_AES(password, plaintext, iv):
    key = password
    padder = PKCS7(128).padder()
    padded_plaintext = padder.update(plaintext.encode()) + padder.finalize()
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    encryptor = cipher.encryptor()
    ciphertext = encryptor.update(padded_plaintext) + encryptor.finalize()
    return iv + ciphertext


plaintext = "0xD{}"
password = getIv()
iv = password

ciphertext = encrypt_AES(password, plaintext, iv)
print(ciphertext.hex())
