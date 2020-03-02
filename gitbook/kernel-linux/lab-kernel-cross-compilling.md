# \[LAB\] Kernel Cross-Compilling

Nesta atividade, os fontes do kernel Linux serão baixados e a partir deles, será realizada a configuração para compilar uma imagem para a RPi3, a compilação da imagem, a gravação na RPi3 e a inicialização do kernel através do U-Boot.

### Baixando os fontes do kernel Linux

A Raspberry Pi Foundation fornece os fontes do kernel para as placas RPi em seu [repositório oficial](%20https://github.com/raspberrypi/linux) e estes foram os fontes baixados para esta atividade. Assim como outras ferramentas, eles se encontram no diretório `∼/dsle20/dl/kernel/linux-rpi-4.14.y.zip`. Crie uma pasta chamada kernel dentro de `dsle2020` e em seguida, extraia os fonte do kernel nela e entre no diretório extraído:

```text
cd ~/dsle20
mkdir kernel
cd kernel
unzip ~/dsle20/dl/kernel/linux-rpi-4.14.y.zip
cd linux-rpi-4.14.y
```

### Configurando o kernel

Conforme apresentado em aula, o kernel possui suporte para muitas arquiteturas diferentes. É possível visualizá-las através do diretório arch:

```text
ls arch/
```

```text
alpha  arm64     cris   hexagon  m32r   microblaze  nios2     powerpc  sh     um         xtensa
arc    blackfin  frv    ia64     m68k   mips        openrisc  s390     sparc  unicore32
arm    c6x       h8300  Kconfig  metag  mn10300     parisc    score    tile   x86
```

Além disso, o kernel também possui suporte especifico para a mesma arquitetura, porém de fabricantes diferentes. Por exemplo, mach-bcm refere-se SoCs da Broadcom, mach-exynos a SoCs da Samsung, mach-sti da ST, e assim por diante:

```text
ls arch/arm 
```

```text
boot           mach-at91        mach-imx         mach-netx       mach-sa1100     mach-zynq
common         mach-axxia       mach-integrator  mach-nomadik    mach-shmobile   Makefile
configs        mach-bcm         mach-iop13xx     mach-nspire     mach-socfpga    mm
crypto         mach-berlin      mach-iop32x      mach-omap1      mach-spear      net
firmware       mach-clps711x    mach-iop33x      mach-omap2      mach-sti        nwfpe
include        mach-cns3xxx     mach-ixp4xx      mach-orion5x    mach-stm32      oprofile
Kconfig        mach-davinci     mach-keystone    mach-oxnas      mach-sunxi      plat-iop
Kconfig.debug  mach-digicolor   mach-ks8695      mach-picoxcell  mach-tango      plat-omap
Kconfig-nommu  mach-dove        mach-lpc18xx     mach-prima2     mach-tegra      plat-orion
kernel         mach-ebsa110     mach-lpc32xx     mach-pxa        mach-u300       plat-pxa
kvm            mach-efm32       mach-mediatek    mach-qcom       mach-uniphier   plat-samsung
lib            mach-ep93xx      mach-meson       mach-realview   mach-ux500      plat-versatile
mach-actions   mach-exynos      mach-mmp         mach-rockchip   mach-versatile  probes
mach-alpine    mach-footbridge  mach-moxart      mach-rpc        mach-vexpress   tools
mach-artpec    mach-gemini      mach-mv78xx0     mach-s3c24xx    mach-vt8500     vdso
mach-asm9260   mach-highbank    mach-mvebu       mach-s3c64xx    mach-w90x900    vfp
mach-aspeed    mach-hisi        mach-mxs         mach-s5pv210    mach-zx         xen
```

Como pode-se perceber, o suporte do kernel Linux às mais variadas plataformas é bem grande. Além dos exemplos acima, existem ainda muitos arquivos de configurações prévias, relacionados a diferentes placas para cada arquitetura. Observe:

```text
ls arch/arm/configs/ 
```

```text
acs5k_defconfig           eseries_pxa_defconfig  mps2_defconfig        rpc_defconfig
acs5k_tiny_defconfig      exynos_defconfig       multi_v4t_defconfig   s3c2410_defconfig
am200epdkit_defconfig     ezx_defconfig          multi_v5_defconfig    s3c6400_defconfig
aspeed_g4_defconfig       footbridge_defconfig   multi_v7_defconfig    s5pv210_defconfig
aspeed_g5_defconfig       gemini_defconfig       mv78xx0_defconfig     sama5_defconfig
assabet_defconfig         h3600_defconfig        mvebu_v5_defconfig    shannon_defconfig
at91_dt_defconfig         h5000_defconfig        mvebu_v7_defconfig    shmobile_defconfig
axm55xx_defconfig         hackkit_defconfig      mxs_defconfig         simpad_defconfig
badge4_defconfig          hisi_defconfig         neponset_defconfig    socfpga_defconfig
bcm2709_defconfig         imote2_defconfig       netwinder_defconfig   spear13xx_defconfig
bcm2835_defconfig         imx_v4_v5_defconfig    netx_defconfig        spear3xx_defconfig
bcmrpi_defconfig          imx_v6_v7_defconfig    nhk8815_defconfig     spear6xx_defconfig
cerfcube_defconfig        integrator_defconfig   nuc910_defconfig      spitz_defconfig
clps711x_defconfig        iop13xx_defconfig      nuc950_defconfig      stm32_defconfig
cm_x2xx_defconfig         iop32x_defconfig       nuc960_defconfig      sunxi_defconfig
cm_x300_defconfig         iop33x_defconfig       omap1_defconfig       tango4_defconfig
cns3420vb_defconfig       ixp4xx_defconfig       omap2plus_defconfig   tct_hammer_defconfig
colibri_pxa270_defconfig  jornada720_defconfig   orion5x_defconfig     tegra_defconfig
colibri_pxa300_defconfig  keystone_defconfig     palmz72_defconfig     trizeps4_defconfig
collie_defconfig          ks8695_defconfig       pcm027_defconfig      u300_defconfig
corgi_defconfig           lart_defconfig         pleb_defconfig        u8500_defconfig
davinci_all_defconfig     lpc18xx_defconfig      prima2_defconfig      versatile_defconfig
dove_defconfig            lpc32xx_defconfig      pxa168_defconfig      vexpress_defconfig
dram_0x00000000.config    lpd270_defconfig       pxa255-idp_defconfig  vf610m4_defconfig
dram_0xc0000000.config    lubbock_defconfig      pxa3xx_defconfig      viper_defconfig
dram_0xd0000000.config    magician_defconfig     pxa910_defconfig      vt8500_v6_v7_defconfig
ebsa110_defconfig         mainstone_defconfig    pxa_defconfig         xcep_defconfig
efm32_defconfig           mini2440_defconfig     qcom_defconfig        zeus_defconfig
em_x270_defconfig         mmp2_defconfig         raumfeld_defconfig    zx_defconfig
ep93xx_defconfig          moxart_defconfig       realview_defconfig
```

Perceba que a maioria das ferramentas de desenvolvimento para Sistemas Linux Embarcado seguem um padrão de configuração no intuito de facilitar o processo para o desenvolvedor. 

O processo para carregar um arquivo de configuração prévia do kernel, é o mesmo como no crosstool-ng e U-Boot. No entanto, por padrão o kernel considera a mesma arquitetura da maquina de desenvolvimento e, portanto, é necessário configurar a arquitetura para ARM. O arquivo de configuração da RPi3 é o `bcm2709_defconfig`:

```text
export ARCH=arm
make bcm2709_defconfig
```

A partir deste momento, as configurações básicas para compilar um kernel funcional para a RPi 3 foram carregadas e salvas em um arquivo chamado .`config` no diretório raiz dos fontes do kernel. Antes de compilar, acesse o `menuconfig` e verifique a quantidade de funcionalidades, drivers, protocolos de comunicação que o kernel oferece suporte:

```text
make menuconfig
```

Antes de compilar o kernel é necessário definir também o toolchain, pois por padrão o processo de build do kernel irá utilizar as ferramentas nativas. Assim, defina a variável `CROSS_COMPILE` e compile o kernel:

```text
export CROSS_COMPILE=arm-linux-
make -j4
```

Ao final do processo de compilação, as imagens geradas se encontrarão no diretório boot da arquitetura utilizada:

```text
ls -l arch/arm/boot
```

### Compilando o Device Tree

A RPi 3 faz uso de Device Tree para disponibilizar as informações de hardware ao kernel. Os fontes de Device Tree fornecidos encontram-se na pasta `arch//boot/dts`:

```text
ls arch/arm/boot/dts
```

A lista é bem longa. Os fontes para a RPi 3 e RPi 3 Plus são ****`bcm2710-rpi-3-b.dts` e `bcm2710-rpi-3-b- plus.dts` respectivamente. Compile de acordo com sua placa:

```text
make bcm2710-rpi-3-b.dtb
```

ou

```text
make bcm2710-rpi-3-b-plus.dtb
```

Após a compilação, o objeto final especificado em um dos comandos acima, estará disponível na pasta `arch/arm/boot/dts`.

### Gravando as novas imagens e bootando a RPi3

Agora é com você. Com as explicações dadas em aula em conjunto com as atividades anteriores, você deverá ser capaz de realizar esta etapa. Copie os arquivos recém-compilados para a RPi via `scp`:

* Faça um backup do script do U-Boot \(`boot.src`\) com o comando `cp`;
* Faça também um backup do Device Tree fornecido pelo Raspian \(`bcm2710-rpi-3-b.dtb`\);
* Todos esses arquivos encontram-se na partição `/boot/` do seu cartão SD;
* Após realizar os backups, gere um novo `boot.scr` com a ferramenta `mkimage` do U-Boot alterando a imagem do kernel para `zImage`;
* Copie os seguintes arquivos na sua partição `/boot`: `zImage`, `bcm2710-rpi-3-b.dtb` e `boot.scr`.
* Para testar se o prodimento funcionou podemos obter a versão do kernel através do comando `uname -r` ou mesmo `dmesg | grep Linux`. Invoque os comandos antes e depois de da prática.

