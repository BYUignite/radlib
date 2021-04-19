import re
import glob

p = glob.glob('/home/vbl22/codes/radlib/installed/lib/py*', recursive=False)[0]

p = re.search(r'python[0-9].[0-9]$', p)
p = p.group()

p = '/home/vbl22/codes/radlib/installed/lib/'+p+'/site-packages'

print("\n\n*********************** Installation complete *************************")
print("   To use the Python interface, update your PYTHONPATH environment variable:")
print("   For example, on Linux/MAC Put the following in your .bashrc file:")
print(f'\n     export PYTHONPATH="{p}:$PYTHONPATH"')
