# Отчет по использованию Асинхроности/Многопоточности
## Сервер (Леонард)
1. Используется Асинхронный HTTP сервер, который запускается на нескольких потоках `std::jthread`
   
   [Ccылка на код HTTP сервера](https://github.com/MrLeonardPak/Calmgram/blob/api_server_28_05/api_server/libs/boost/server/src/async_http_server.cc)

2. В виду использование потоков, для работы с PostgreSQL через библиотеку libpqxx, которая нативно не умеет работать с потоками, были написаны создание и сипользование пула соединений с использованием  `std::mutex  std::condition_variable std::scoped_lock  std::unique_lock`
   
   [Ccылка на код контроллера БД](https://github.com/MrLeonardPak/Calmgram/blob/api_server_28_05/api_server/libs/database/src/postgre_sql.cc)

## Клиент (Иван)

## ML (Алан)

1. Для обучения модели во время работы приложения запускается дополнительный поток `std::thread`, выполняющийся на фоне основного приложения.

   [Ссылка на код ML](https://github.com/MrLeonardPak/Calmgram/tree/integration_2/ML)

