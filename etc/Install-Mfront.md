# How to install Mfront and MGIS



- Install prerequisites  

  ```bash
  sudo apt-get install cmake libboost-all-dev g++ gfortran \
       git libqt5svg5-dev qtwebengine5-dev python3-matplotlib
  ```

  

- Mfront for installation

  ```bash
  PYTHON_VERSION=$(python3 --version|awk '{print $2}'|awk 'BEGIN{FS="."} {print $1 "." $2}')   && \
    export PYTHON_VERSION  && \
    export TFELHOME=$HOME/Install/local/mfront  && \
    cd $HOME/Install/GitPackages  && \
    git clone https://github.com/thelfer/tfel.git mfront-sources   && \
    cd  mfront-sources && \
    git checkout TFEL-3.4.1 && \
    mkdir build  && \
    cd build  && \
    cmake .. -DCMAKE_BUILD_TYPE=Release -Denable-python=ON -Denable-python-bindings=ON  -DCMAKE_INSTALL_PREFIX=$HOME/Install/local/mfront   && \
    make -j 8   && \
    make install
  ```

  

- Prepare a mfront environment file 

  ```bash
    cat >> ${TFELHOME}/mfront-env.sh <<EOF
    export TFELHOME=${TFELHOME}
    export PATH=${TFELHOME}/bin:\$PATH
    export LD_LIBRARY_PATH=${TFELHOME}/lib:\$LD_LIBRARY_PATH
    export PYTHONPATH=${TFELHOME}/lib/python${PYTHON_VERSION}/site-packages/:\$PYTHONPATH
  EOF
  ```

  

  
  

- MGIS installation 

  ```bash
  PYTHON_VERSION=$(python3 --version|awk '{print $2}'|awk 'BEGIN{FS="."} {print $1 "." $2}')   && \
    export PYTHON_VERSION  && \
    export TFELHOME=$HOME/Install/local/mfront  && \
    export MGISHOME=$HOME/Install/local/mgis  && \
    source ${TFELHOME}/mfront-env.sh   && \
    cd $HOME/Install/GitPackages  && \
    git clone https://github.com/thelfer/MFrontGenericInterfaceSupport.git mgis-sources   && \
    cd  mgis-sources && \
    git checkout MFrontGenericInterfaceSupport-1.2.1 && \
    mkdir build  && \
    cd build  && \
    cmake .. -DCMAKE_BUILD_TYPE=Release -Denable-c-bindings=ON -Denable-python-bindings=ON -DCMAKE_INSTALL_PREFIX=$MGISHOME  && \
    make -j 8   && \
    make install
  ```



- Prepare a mgis environment file 

  ```bash
    cat >> ${MGISHOME}/mgis-env.sh <<EOF
    export MGISHOME=${MGISHOME}
    export PATH=${MGISHOME}/bin:\$PATH
    export LD_LIBRARY_PATH=${MGISHOME}/lib:\$LD_LIBRARY_PATH
    export PYTHONPATH=${MGISHOME}/lib/python${PYTHON_VERSION}/site-packages/:\$PYTHONPATH
  EOF
  ```
