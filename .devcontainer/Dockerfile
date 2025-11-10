# Используем официальный базовый образ с GCC 14.2.0
FROM gcc:14.2.0

# Устанавливаем необходимые зависимости: cmake и clangd для анализа кода
# DEBIAN_FRONTEND=noninteractive отключает интерактивные диалоги при установке
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y \
    cmake \
    clangd \
    && rm -rf /var/lib/apt/lists/*
ENV DEBIAN_FRONTEND=dialog

# Создаем рабочую директорию внутри контейнера
WORKDIR /workspace