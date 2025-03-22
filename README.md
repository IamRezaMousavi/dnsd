# Minimalist DNS Server

A lightweight, fast, and resource-efficient DNS server written in C++. Designed for simplicity and minimalism, this DNS server is perfect for systems with very limited resources.

## Features

- **Lightweight**: Extremely low memory and CPU usage.
- **Minimal Dependencies**: Written with only the standard C++ library, no third-party dependencies.
- **Simple Configuration**: Configure the server with a single, clean config file.
- **Command-Line Interface**: Easy-to-use, straightforward command-line for setup and operation.
- **Object-Oriented Design**: Written in modern C++ with a clean and maintainable codebase.

## Getting Started

### Prerequisites

- C++11 or higher
- A working C++ compiler (e.g., `g++` or `clang++`)
- A Linux/Unix-based system (for development and usage)

### Installation

1. Clone the repository

    ```sh
    git clone https://github.com/iamrezamousavi/dnsd.git
    cd dnsd/
    ```

2. Build the project

    ```sh
    make
    ```

3. Run the server

    ```sh
    ./bin/dnsd -f db.conf
    ```

## Usage

Once the server is running, you can point your DNS client to the server's IP and start resolving domain names.
For example, you can test the server using `dig` or `host`:

```sh
dig @localhost -p 5353 cs.vu.nl
```

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue if you find any bugs or have suggestions for improvements.

## License

This project is licensed under the GPL-v3 License - see the [LICENSE](./LICENSE) file for details.

---

Enjoy your lightweight DNS server! If you find it useful, consider giving it a ⭐ on GitHub!
