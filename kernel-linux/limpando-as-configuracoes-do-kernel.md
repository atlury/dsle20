# Limpando as Configurações do Kernel

Normalmente é um padrão dos scripts Makefiles, remover imagens, arquivos objetos, binários, bibliotecas e outros arquivos temporário. Para tal, basta invocar o comando `clean`:

```text
make clean
```

Além de remover todos os arquivos gerados, remove também os de configuração:

```text
make mrproper
```

