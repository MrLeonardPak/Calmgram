SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';

DROP TABLE IF EXISTS
  users,
  chats,
  users_chats,
  messages
  CASCADE;

-- https://www.postgresql.org/docs/current/datatype.html

CREATE TABLE IF NOT EXISTS users (
  id serial PRIMARY KEY,
  "login" varchar(30) NOT NULL unique
  -- pswhash text -- https://www.postgresql.org/docs/14/pgcrypto.html
);

CREATE TABLE IF NOT EXISTS chats (
  id serial PRIMARY KEY
);

-- ManyToMany для пользователя и чатов 
CREATE TABLE IF NOT EXISTS users_chats (
  user_id integer REFERENCES users ON DELETE CASCADE,
  chat_id integer REFERENCES chats ON DELETE CASCADE,
  PRIMARY KEY (user_id, chat_id)
);

CREATE TABLE IF NOT EXISTS messages (
  id serial PRIMARY KEY,
  chat_id integer REFERENCES chats ON DELETE CASCADE,
  owner_id integer REFERENCES users ON DELETE SET NULL,
  "text" text NOT NULL,
  is_marked boolean NOT NULL,
  created timestamp NOT NULL
);
