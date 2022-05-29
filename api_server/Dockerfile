FROM alpine

RUN apk add --no-cache build-base linux-headers cmake libpq-dev git
RUN wget https://boostorg.jfrog.io/artifactory/main/release/1.79.0/source/boost_1_79_0.tar.gz
RUN tar xzf boost_1_79_0.tar.gz -C /usr/include && rm -rf boost_1_79_0.tar.gz