<div align="center">
    <h1> 0x0MemDestruX - 0x0MDX </h1>
</div>

<p div align="justify">
    <bold> Welcome to my project 0x0MDX! This project is a project that provides an interface for bufferoverflow attacks. </bold>
    <br/> <br/>
    The program performs a buffer overflow attack based on the specified IP address and PORT information. Likewise, the program provides the necessary filters to perform a buffer overflow attack. However, this project is still under development. So I will add many more features in the future.
</p>

<br>

<h2> Required Packages for the Project </h2>

<p>
    To run the project smoothly, you need to download the packages shown below. You can install the packages according to the Linux Distro you are using.
</p> 

<h3> Ubuntu </h3>

```sh
sudo apt-get install nasm gcc libgtk-3-dev python3-dev libcario2-dev python3-gi gir1.2-gtk-3.0 libgirepository1.0-dev
```` 

<h3> Fedora </h3>

```sh
sudo dnf install nasm python3-gobject gtk3-devel gobject-introspection-devel cairo-devel
```

<h3> Arch Linux </h3>

```sh
sudo pacman -S nasm python-gobject gtk3 gobject-introspection cairo
```

<p> <b> Now we need to install the pygobject library. You can download it with the following command: </b></p>

```shell
pip install pygobject
```

<br> 

<h2> Compiling and Running the Project</h2>

<p> <b> First, let's clone the project: </b></p>

```shell
git clone https://github.com/devTBenoth/0x0MemDestruX.git
```

<p> <b> Now we need to compile the c project. Let's go to the src directory and run the following command: </b></p>

```shell
cd 0x0MemDestruX/src && make 
```

<p> <b> We are now ready to run the project! Let's go to the gui directory and run the project: </b></p>

```shell
cd ../gui && python3 main.py
```

<br>

<h2> More Details About the Project </h2>

<p>
    I developed the 0x0MDX project using C, Python and Assembly and I still continue to develop it. You can think of the current state as a beta version. In this project, I have listed below what I use programming languages for:
</p>

<ul>
    <li> <b> Python --> </b> I created interface environment using pygobject library. With libraries such as subprocess, I provided the connection with the c project. </li>
</ul>