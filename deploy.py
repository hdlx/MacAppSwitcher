import os
import compileCommon
import shutil

def deploy(arch, writeManifest = False):
    file = compileCommon.CompileRel(arch)
    dir = "./Output/Deploy"
    if not os.path.exists(dir):
        os.makedirs(dir)
    zipFile = f"{dir}/MacAppSwitcher_{arch}"
    srcDir = f"./Output/Release/{arch}"
    shutil.make_archive(zipFile, "zip", srcDir)

deploy("x86_64")
deploy("aarch64")