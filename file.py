def file_check(name):
    file = open(name, 'r')
    lines = file.readlines()

    if( len(lines) % 2 != 0):
        print("ERROR")
        return
    print("[" + str(name) + "] length: " + str(len(lines)) )
    sum = 0
    for i in range(int(len(lines) / 2)):
        if(lines[2*i][0:3] != "Pub" or lines[2*i + 1][0:3] != "Sub"):
            print("ERROR")
            break
        Pub = float(lines[2*i][4:])
        Sub = float(lines[2*i + 1][4:])
        print("[" + str(i) + "] " + str(Sub - Pub))
        sum = sum + (Sub - Pub)
    print("[Avg] "+ str(sum / int(len(lines) / 2)))
    file.close()

if __name__ == "__main__":
    file_check("test.txt")