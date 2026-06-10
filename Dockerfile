# Stage 1: build and test
FROM gcc:14 AS builder
RUN apt-get update && apt-get install -y cmake build-essential cppcheck

WORKDIR /app
COPY . .

# check src folder
RUN cppcheck --enable=all --error-exitcode=1 --std=c++20 --suppress=missingInclude \
    --suppress=missingIncludeSystem \
    --suppress=unusedFunction \
    --suppress=unmatchedSuppression \
    src/

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