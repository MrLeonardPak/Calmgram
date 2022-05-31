# Отчет по использованию CI

## API Server (Леонард)

[![CI Application Server](https://github.com/MrLeonardPak/Calmgram/actions/workflows/ci_api_server.yml/badge.svg)](https://github.com/MrLeonardPak/Calmgram/actions/workflows/ci_api_server.yml)

### CI запускает в начале build, и при успешном запускает тесты под санитайзером и валгриндом по отдельности
![CI_Server](img/CI_Server.png)  

### Тесты написаны на Use Case-ы и на Handler-ы
Пример (С valgrind)
![CI_Server](img/Sever_Test_1.png)  
![CI_Server](img/Sever_Test_2.png)  

[Ссылка на CI](https://github.com/MrLeonardPak/Calmgram/blob/api_server_28_05/.github/workflows/ci_api_server.yml)
[Ссылка на тесты](https://github.com/MrLeonardPak/Calmgram/tree/api_server_28_05/api_server/tests)


## ML (Алан)

[![.github/workflows/ci.yml](https://github.com/MrLeonardPak/Calmgram/actions/workflows/ci.yml/badge.svg)](https://github.com/MrLeonardPak/Calmgram/actions/workflows/ci.yml)
