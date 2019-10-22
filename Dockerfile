# To Build: docker build --no-cache -t pbui/cse-30341-fa19-project04 . < Dockerfile

FROM	    ubuntu:18.04
MAINTAINER  Peter Bui <pbui@nd.edu>

RUN	    apt update -y

# Run-time dependencies
RUN	    apt install -y build-essential
