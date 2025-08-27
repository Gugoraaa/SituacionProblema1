# Proyecto C++ con CMake

Este proyecto C++ utiliza CMake para la gestión de compilación y construcción. Esta guía te ayudará a configurar el entorno de desarrollo y compilar el proyecto en diferentes sistemas operativos.

## 📋 Requisitos del Sistema

### Herramientas Necesarias
- **CMake** - Sistema de construcción multiplataforma
- **Compilador C++** - `g++` o equivalente
- **Make** - Herramienta de automatización de construcción

### Versiones Mínimas Requeridas
| Herramienta | Versión Mínima |
|-------------|----------------|
| CMake       | 3.10+          |
| g++         | 7.0+           |
| Make        | 4.0+           |

## 🛠️ Instalación

### Ubuntu / Debian

```bash
# Actualizar el sistema
sudo apt update
sudo apt upgrade -y

# Instalar herramientas de desarrollo
sudo apt install cmake build-essential make

# Verificar instalación
cmake --version
g++ --version
make --version
```

### macOS

```bash
# Instalar Homebrew (si no está instalado)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Instalar herramientas de desarrollo
brew install cmake gcc make

# Verificar instalación
cmake --version
g++ --version
make --version
```

### Windows

#### Opción 1: Instalación Nativa
1. **CMake**: Descargar desde [cmake.org](https://cmake.org/download/) y añadir al PATH
2. **MinGW**: Instalar para obtener `g++` y `make`

#### Opción 2: WSL (Recomendado)
```bash
# Instalar Ubuntu desde Microsoft Store, luego:
sudo apt update
sudo apt install cmake build-essential make
```

## Compilación y Ejecución

### Paso 1: Clonar el Repositorio
```bash
git clone <URL_DEL_REPOSITORIO>
cd <nombre_del_directorio_del_proyecto>
```

### Paso 2: Configurar con CMake
```bash
cmake .
```

### Paso 3: Compilar el Proyecto
```bash
make
```

### Paso 4: Ejecutar el Programa
```bash
# Compilar y ejecutar automáticamente
make run


```

##  Comandos de Limpieza

```bash
# Limpiar archivos de construcción
make clean
```

## 📖 Referencia Rápida

| Acción | Comando |
|--------|---------|
| Configurar proyecto | `cmake .` |
| Compilar | `make` |
| Ejecutar | `make run` |
| Limpiar | `make clean` |

