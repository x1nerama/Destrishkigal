import gi
import subprocess
import os
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

class myApp(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title="My App")

        self.set_default_size(600, 300)
        self.connect("destroy", Gtk.main_quit)

        fixed = Gtk.Fixed()
        self.add(fixed)

        # Number Textbox
        number = Gtk.Entry()
        fixed.put(number, 20, 40)

        # Spin button oluştur ve sabit düzene ekle
        adjustment = Gtk.Adjustment(0, 0, 100, 1, 10, 0)
        self.spinbutton = Gtk.SpinButton()
        self.spinbutton.set_adjustment(adjustment)
        self.spinbutton.set_numeric(True)
        fixed.put(self.spinbutton, 50, 50)

        # Butonu oluştur ve sabit düzene ekle
        button = Gtk.Button(label="Click me Bro!")
        button.set_size_request(50, 50)
        button.connect("clicked", self.on_button_clicked)
        fixed.put(button, 50, 80)

        self.show_all()

    def on_button_clicked(self, widget):
        nm = self.spinbutton.get_value_as_int()
        p = subprocess.Popen(['./program', str(nm)], stdout=subprocess.PIPE, env={'LD_LIBRARY_PATH': './'})
        out, err = p.communicate()
        print(out.decode())

def main():
    win = myApp()
    Gtk.main()

if __name__ == "__main__":
    main()