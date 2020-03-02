# Device Tree

De forma geral, o _devicetree_ é uma estrutura de dados que descreve os componentes de hardware de uma plataforma ou computador. Assim, o sistema operacional, mais precisamente o kernel, pode manipular esses componentes, por exemplo, processador, memória, barramento e outros periféricos.

Um device tree é uma forma flexivel de definir componentes de hardware de um sistema. Usualmente, o device tree é carregado por um bootloader e passado então para o kernel. Além disto, é possível agrupar o device tree com a imagem do kernel. Embora seja possível agrupar o device tree com a própria imagem do kernel para atender o gerenciamento, uma vez que os bootloaders podem não lidar com eles separadamente.

Informações mais precisas é fortemente recomentado consultar o [site oficial do DeviceTree](http://devicetree.org).

### Fundamentos do Device Tree

Como diversas plataformas embarcadas possuem dspositivos de hardware que o kernel não pode identificar dinamicamente, existe duas formas de se fazer isso. Em algumas plataformas, os componentes e dispositivos são descritos através de códigos em C diretamente dentro dos fontes do kernel. Contudo alguns optam por uma abordagem mais flexível que é a utilização de uma linguagem de descrição de harware especial, o Device Tree.

O Device Tree é uma estrutura de dados que descreve o tipo e a configuração dos dispositivos de hardware. Em especial, são descritos os componentes físicos anexados ao barramento do processador.

O formato é derivado de um bootloader da Sun Microsystem chamado de OpenBoot, que foi formalizado como as especificações de padrão IEEE. Ele foi empregado em arquiteturas para Macintosh baseados em PPC e em PPC Linux também. Em seguida, foi adotado em diversas implementações de ARM Linux e outras tantas arquiteturas.

Na prática é um arquivo com extensão .dts, este arquivo é composto por uma estrutura hierárquica que descreve especificamente os componentes de hardware que compõem o sistema.

Por exemplo, é possível se descrever dispositivos de hardware externos conectados à barramentos I2C. Ou mesmo, descrever certas multiplexações de pinos do processador, ou quis sinais do SoC estarão disponíveis no conector externo.

Um exemplo básico de Device Tree pode ser visto no código abaixo.

```text
cpus {
    cpu@0 {
        compatible = "arm,cortex-a9";
    };
    cpu@1 {
        compatible = "arm,cortex-a9";
    };
};

serial@101F0000 {
    compatible = "arm,pl011";
};

serial@101F2000 {
    compatible = "arm, pl011";
};

gpio@101F3000 {
    compatible = "arm, pl061";
}; 
interrupt-controller@10140000 {
    compatible = "arm, pl190";
};  

spi@10115000 {
    compatible = "arm, pl022";
};        
```

Como mecnionado as Device Tree, estruturas de dados que descrevem os componentes de hardware, são dependêntes de cada plataforma, já que descrever suas especificações.

Assim como os arquivos de configuração do kernel Linux, é possível listar as Device Trees disponíveis nos fontes do kernel:

```text
ls arch/arm/boot/dts
```

```text
aks-cdu.dts
alphascale-asm9260-devkit.dts
alphascale-asm9260.dtsi
alpine-db.dts
alpine.dtsi
am335x-baltos.dtsi
am335x-baltos-ir2110.dts
am335x-baltos-ir3220.dts
am335x-baltos-ir5221.dts
am335x-baltos-leds.dtsi
am335x-base0033.dts
am335x-boneblack-common.dtsi
am335x-boneblack.dts
am335x-boneblack-wireless.dts
am335x-boneblue.dts
am335x-bone-common.dtsi
am335x-bone.dts
[..]
```

Dentre estas é possível, temos interesse na descrição da plataforma que estamos utilizando no treinamento, então filtrando as arquiteturas pelo nosso chip:

```text
ls arch/arm/boot/dts | grep bcm2710-
```

```text
bcm2710-rpi-3-b.dtb
bcm2710-rpi-3-b.dts
bcm2710-rpi-3-b-plus.dtb
bcm2710-rpi-3-b-plus.dts
bcm2710-rpi-cm3.dtb
bcm2710-rpi-cm3.dts
```

Assim, podemos visualizar o nosso Device Tree de interesse

```text
cat bcm2710-rpi-3-b.dts
```

```text
/dts-v1/;

#include "bcm2710.dtsi"
#include "bcm283x-rpi-smsc9514.dtsi"

/ {
	compatible = "raspberrypi,3-model-b", "brcm,bcm2837";
	model = "Raspberry Pi 3 Model B";

	chosen {
		bootargs = "8250.nr_uarts=1";
	};

	aliases {
		serial0 = &uart1;
		serial1 = &uart0;
	};
};

&gpio {
	spi0_pins: spi0_pins {
		brcm,pins = <9 10 11>;
		brcm,function = <4>; /* alt0 */
	};

	spi0_cs_pins: spi0_cs_pins {
		brcm,pins = <8 7>;
		brcm,function = <1>; /* output */
	};

	i2c0_pins: i2c0 {
		brcm,pins = <0 1>;
		brcm,function = <4>;
	};

....
```

No caso da Raspberry 3 Model B+, devemos utilizar o seguinte Device Tree:

```text
cat bcm2710-rpi-3-b-plus.dts
```

### Compilando o Device Tree

Existe um compilador específico para Device Trees o `dtc`. Este está disponível no diretório `scripts/dtc`. 

Para realizar a compilação das estruturas de Device Trees de todas as placas/arquiteturas habilitadas no arquivo de configuração do kernel Linux, basta executar o comando `make`, especificando a variável de da arquitetura e a ferramenta de cross-compilação:

```text
make ARCH=arm CROSS_COMPILE=arm-linux- dtbs
```

E para compilar somente o Device Tree da sua placa, no nosso caso a RPi 3, é necessário identificar o nome do arquivo de configuração \(arquivo com a extensão `.dts`\) e executar o comando `make` sobre o mesmo.

```text
make bcm2710-rpi-3-b.dtb
```

O arquivo compilado, `.dtb`, é disponibilizado dentro do diretório dos Device Trees, `arch/arm/boot/dts`.

### Realizando o boot com o U-Boot

Como apresentado anteriormente, nas versões mais recentes do U-Boot é possível carregar a imagem zImage. Em versões antigas necessitavam do arquivo uImage.

O U-Boot também suporta passar o arquivo compilado, o Device Tree Blob \(.dtb\), como um parâmetro do kernel. 

Conforme o procedimento já realizado, o processo básco envolve, carregar o arquivo zImage no endereco X da memória RAM e o arquivo .dtb no endereço Y da memória RAM. E Iniciar o kernel Linux com o comando:

```text
bootz X - Y
```

Onde o símbolo -, india a ausência de um initramfs. Caso haja dúvidas  é possível reler o material da seção U-Boot, em especial o roteiro prático do Laboratório Bootloader.

