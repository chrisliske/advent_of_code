import hashlib
  
# initializing string
key = "iwrupvqb"
test = "0"
md5 = "ZZZZZ"

while md5 != "000000":
    test = str(    int(test) + 1    )
    full = key + test
    result = hashlib.md5(full.encode())

    md5 = str(result.hexdigest()[0] + result.hexdigest()[1] + result.hexdigest() [2] + result.hexdigest()[3] + result.hexdigest()[4] + result.hexdigest()[5])

    print("trying: " + test)


# printing the equivalent hexadecimal value.
print("Secret key used:         " + key)
print("Number added:            " + test)
print("string to pass to hash:   " + full)
print("Result:                  " + result.hexdigest())
