<!--
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]

[![forthebadge](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/built-with-love.svg)](https://forthebadge.com)

# Projet Logiciel Transversal : ENSEA<sup>i</sup>

  [![c++ version][cpp-ver-shield]][cpp-ver]
  [![software version][version-shield]][last_version]

  </div>
</p>

<!-- TABLE OF CONTENTS -->
## Table of Contents

* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
  * [Basic Testing](#basic-testing)
* [Release History](#release-history)
* [Built With](#built-with)
* [Contributing](#contributing)
* [License](#license)


<!-- Release 1.Final -->








<!-- Introduction -->
## Introduction

The [*PLT*] **P**rojet **L**ogiciel **T**ransversal (Transversal Software Project) is the third year project in specialization [*IS*] **I**nformatique et **S**ystèmes (computer science and system) at [ENSEA](https://www.ensea.fr/fr). 


<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

Resynchronize the package index files 
```sh
sudo apt-get update
```

Install with apt-get
```sh
sudo apt-get install build-essential \
dia \
libsfml-dev libxml2-dev libmicrohttpd-dev libboost-all-dev \
python3 python3-pip \
lcov gcovr
```

Install python package with pip (or pip3)
```sh
pip install gcovr
```

### Installation

1. Clone the repo
```sh
git clone https://github.com/[username]/[reponame]
cd plt
```

2. Build it
```sh
plt$ make
```

3. Test it
```sh
plt$ make test
``` 

<!-- USAGE -->
## Usage

## Basic Testing

Print a hello world message
```sh
plt$ bin/client hello
```

Execute unit testing
```sh
plt$ make test
```

Check code coverage
```sh
plt$ cd build
plt$ make code-coverage
```

<!-- RELEASE HISTORY-->
## Release History
* <a href="https://github.com/Mamdad0u/plt/releases/tag/2.1">2.1</a>
    * Rapport section 3 : Description et Conception des du rendu selon les états du jeu
    * Code : Implémentation du rendu du jeu en fonction de ses états.


* <a href="https://github.com/Mamdad0u/plt/releases/tag/1.final">1.final</a>
    * Rapport section 2 : Description et Conception des états
    * Code : Implémentation des tests unitaires d'états. Test avec `make test`

* <a href="https://github.com/Mamdad0u/plt/releases/tag/1.1">1.1</a>
    * Environnement de d´eveloppement
    * Ajout des ressources utilisées
    * Rapport section 1 : Présentation générale
    * Code : Affichage message `./bin/client hello`

## Built With

* [SFML](https://github.com/SFML/SFML)
* [Dia Diagram Editor](http://dia-installer.de/index.html.en)
* [dia2code](http://dia2code.sourceforge.net/)
* [libxml2](http://www.xmlsoft.org/)
* [JsonCpp](https://github.com/open-source-parsers/jsoncpp)

<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, 
inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<!-- LICENSE -->
## License

Distributed under the MIT License. See [LICENSE][license-url] for more information.

<!-- MARKDOWN LINKS & IMAGES -->

[contributors-shield]: https://img.shields.io/github/contributors/Mamdad0u/plt.svg?style=flat-square
[contributors-url]: https://github.com/Mamdad0u/plt/graphs/contributors

[forks-shield]: https://img.shields.io/github/forks/Mamdad0u/plt.svg?style=flat-square
[forks-url]: https://github.com/Mamdad0u/plt/network/members

[stars-shield]: https://img.shields.io/github/stars/Mamdad0u/plt.svg?style=flat-square
[stars-url]: https://github.com/Mamdad0u/plt/stargazers

[issues-shield]: https://img.shields.io/github/issues/Mamdad0u/plt.svg?style=flat-square
[issues-url]: https://github.com/Mamdad0u/plt/issues

[license-shield]: https://img.shields.io/github/license/Mamdad0u/plt?style=flat-square
[license-url]: https://github.com/Mamdad0u/plt/blob/master/LICENSE

[cpp-ver-shield]: https://img.shields.io/badge/C%2B%2B-11-blue.svg
[cpp-ver]: https://en.wikipedia.org/wiki/C%2B%2B11

[version-shield]: https://img.shields.io/github/v/release/Mamdad0u/plt?style=flat-square
[last_version]: https://github.com/Mamdad0u/plt/releases/tag/1.final
