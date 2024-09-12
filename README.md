# philosophers-42
## Aqui estão as coisas que você precisa saber se quiser ter sucesso nesta tarefa:
- Um ou mais filósofos sentam-se em uma mesa redonda.
Há uma grande tigela de espaguete no meio da mesa.
- Os filósofos alternadamente comem, pensam ou dormem.
Enquanto comem, não pensam nem dormem; enquanto pensam,
não comem nem dormem; e, claro, enquanto dormem,
não comem nem pensam.
- Também há garfos na mesa. Há tantos garfos quanto filósofos.
- Como servir e comer espaguete com apenas um garfo é muito inconveniente, um filósofo pega o
garfo direito e o esquerdo para comer, um em cada mão.
- Quando um filósofo termina de comer, ele coloca seus garfos de volta na mesa e começa a dormir.
Uma vez acordado, ele começa a pensar novamente. A simulação para quando um filósofo morre
de fome.
- Todo filósofo precisa comer e nunca deve passar fome.
- Os filósofos não falam entre si.
- Os filósofos não sabem se outro filósofo está prestes a morrer.
- Não é preciso dizer que os filósofos devem evitar a morte!

## Modo de compilação
```bash
./philo [número_de_filósofos] [tempo_para_morrer] [tempo_para_comer] [tempo_para_dormir] <[número_de_vezes_cada_filósofo_deve_comer] esse parametro é opcional>
```
## Explicando os parametros

- <strong> número_de_filósofos </strong>: O número de filósofos e também o número
de garfos.

-  <strong> tempo_de_morrer (em milisegundos) </strong>: Se um filósofo não começar a comer antes de terminar o tempo dele de morrer em milissegundos
contando desde o início da sua última refeição ou do início da simulação, ele morre.
- <strong> tempo_de_comer(em milisegundos) </strong> : O tempo que um filósofo leva para comer.
Durante esse tempo, eles precisarão segurar dois garfos.
- <strong> tempo_para_dormir (em milissegundos)</strong> : O tempo que um filósofo passará dormindo.
- número_de_vezes_que_cada_filósofo_deve_comer (argumento opcional): Se todos
filósofos comeram pelo menos [número_de_vezes_que_cada_filósofo_deve_comer vezes], a simulação
para. Se não for especificado, a simulação para quando um filósofo morre.
