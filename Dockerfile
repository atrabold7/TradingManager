# Stage 1: build and test
FROM gcc:14 AS builder
RUN apt-get update && apt-get install -y cmake build-essential

WORKDIR /app
COPY . .

# build
RUN cmake -B build -DCMAKE_CXX_STANDARD=20
RUN cmake --build build

# start testing
RUN ./build/tests/unit_tests

# Stage 2: final image
FROM debian:bookworm-slim
WORKDIR /app
# copy image from builder-stage
COPY --from=builder /app/build/TradingManager .
CMD ["./TradingManager"]