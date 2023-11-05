import winreg

def returnMouseReg():
    names = []
    data = []
    entries = []
    try:
        with winreg.OpenKey(winreg.HKEY_CURRENT_USER, r"Control Panel\Mouse") as key:
            i = 0
            while True:
                try:
                    name, value, _ = winreg.EnumValue(key, i)
                    names.append(name)
                    data.append(value)
                    i += 1
                except OSError as e:
                    if e.errno == 22:  # Registry EOF Error
                        break
    except FileNotFoundError:
        print(f"Registry key '{key_path}' not found")
    entries.append(names)
    entries.append(data)
    return entries

def isAccelOn():
    try:
        with winreg.OpenKey(winreg.HKEY_CURRENT_USER, r"Control Panel\Mouse") as key:
            acceleration = int(winreg.QueryValueEx(key, "MouseSpeed")[0])
            print(acceleration)
            return acceleration == 1
        winreg.CloseKey(key)
    except FileNotFoundError:
        return


mouseReg = returnMouseReg()
for i in range(len(mouseReg[0])):
  print((mouseReg[0])[i], (mouseReg[1])[i])

print(isAccelOn())