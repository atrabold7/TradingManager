FROM gcc:14

RUN apt-get update && apt-get install -y \
    cmake \
    build-essential

WORKDIR /app
# Wir kopieren alles, aber wir bauen noch NICHT während des `docker build`
COPY . .