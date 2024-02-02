# 设置环境变量
export ARCH=arm64
export SUBARCH=arm64
export DTC_EXT=dtc
export PATH="$(pwd)/aarch64-linux-android-4.9/bin:$(pwd)/arm-linux-androideabi-4.9/bin:$(pwd)/linux-x86/clang-r399163/bin:$PATH"

# 构建参数，使用nproc自动检测核心数
args="-j$(nproc) \
ARCH=arm64 \
SUBARCH=arm64 \
O=out \
CC=clang \
CROSS_COMPILE=aarch64-linux-android- \
CROSS_COMPILE_ARM32=arm-linux-androideabi- \
CLANG_TRIPLE=aarch64-linux-gnu-"


# 清理构建目录
make clean && make mrproper
rm kernel.log && rm -rf out 
mkdir -p out

# 构建
make ${args} vendor/atom_user_defconfig
make ${args} 2>&1 | tee kernel.log

cd 0
chmod +x magiskboot
gzip -dk boot.img.gz
./magiskboot unpack boot.img
mv -f ../out/arch/arm64/boot/Image.gz-dtb kernel
./magiskboot repack boot.img
