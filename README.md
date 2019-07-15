# Projetos para Sistemas Embarcados

### Como escrever em uma placa

- Executar o comando `west build -b <nome_da_placa>` para fazer o build do projeto.
- Executar o comando `west flash` para escrever na placa.
- Se a placa estiver com problemas na escrita, utilize o comando `nrfjprog --reset -f <ref_da_placa>`.

## Utilizando Minicom
- Instale o [minicom](http://processors.wiki.ti.com/index.php/Setting_up_Minicom_in_Ubuntu) na sua máquina.
- Execute o comando `minicom` (Recomenda-se executar o minicom em uma nova aba do terminal).


