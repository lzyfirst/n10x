# 执行自定义脚本
rm -rf KernelSU
./kernelsu.sh
sed -i "5s/.*/EXTRAVERSION = -LZY-$(date +%Y-%m-%d)/" Makefile

# 安装必要的包
apt-get update
apt-get full-upgrade -y
apt-get install -y bc bison build-essential ccache curl flex g++-multilib gcc-multilib git git-lfs gnupg gperf imagemagick lib32ncurses5-dev lib32readline-dev lib32z1-dev libelf-dev liblz4-tool libncurses5 libncurses5-dev libsdl1.2-dev libssl-dev libxml2 libxml2-utils lzop pngcrush rsync schedtool squashfs-tools xsltproc zip zlib1g-dev
apt-get clean
apt-get autoremove --purge

# 克隆指定分支的仓库
git clone --depth 1 -b llvm-r399163b -- https://android.googlesource.com/platform/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9
git clone --depth 1 -b llvm-r399163b -- https://android.googlesource.com/platform/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.9
git clone --depth 1 -b llvm-r399163b -- https://android.googlesource.com/platform/prebuilts/clang/host/linux-x86 