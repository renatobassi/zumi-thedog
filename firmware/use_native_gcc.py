Import("env")

import os
import shutil

# O alvo native chama o g++ do sistema. No Windows ele costuma não estar no PATH;
# o PlatformIO já baixa o MinGW para outros alvos. Usa esse, se o sistema não tiver o seu.

if os.name == "nt" and shutil.which("g++") is None:
    bin_dir = os.path.join(os.path.expanduser("~"), ".platformio", "packages", "toolchain-gccmingw32", "bin")
    if os.path.isdir(bin_dir):
        env.PrependENVPath("PATH", bin_dir)
        os.environ["PATH"] = bin_dir + os.pathsep + os.environ.get("PATH", "")

if os.name == "nt":
    env.Append(LINKFLAGS=["-static-libgcc", "-static-libstdc++", "-static"])
    if env["PIOENV"] == "preview":
        env.Append(LINKFLAGS=["-mwindows"])
