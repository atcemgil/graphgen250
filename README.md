# graphgen250
Generates simple example graphs for the CMPE250 Data Structures Course at Bogazici University, Istanbul, Turkey.

## Usage

You need to have docker cli installed on your machine to run this project

- Clone this repository
- run `docker build . -t graphgen` inside the repository folder to build the container
- run `docker run -d -p 8880:8880 graphgen:latest` to run the webserver
- test that [localhost:8880/plot_mst](http://localhost:8880/plot_mst) renders an mst on your browser
