import gi, subprocess, os
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, Gdk
dirName = __file__

class bufferGUI(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title="Bufferoverflow GUI")
        self.set_default_size(600, 450)
        self.set_resizable(False)
        self.connect("destroy", Gtk.main_quit)

        # Enable Css Provider
        cssProvider = Gtk.CssProvider()
        cssPath = "css/style.css"
        cssProvider.load_from_path(cssPath)

        # Get Style Context
        styleContext = Gtk.StyleContext()
        styleContext.add_provider_for_screen(
            Gdk.Screen.get_default(),
            cssProvider,
            Gtk.STYLE_PROVIDER_PRIORITY_APPLICATION
        )
        styleContext.add_class(Gtk.STYLE_CLASS_ENTRY)

        # Create Fixed
        fixed = Gtk.Fixed()
        self.add(fixed)

        # Main Label
        self.mLabel = Gtk.Label()
        self.mLabel.set_markup("<b> BUFFEROVERFLOW GUI </b>")
        self.mLabel.get_style_context().add_class("mainHeader")
        fixed.put(self.mLabel, 3, 10)

        # IP Label
        self.ipLabel = Gtk.Label(label="IP ADDRESS")
        self.ipLabel.get_style_context().add_class("ipLabel")
        fixed.put(self.ipLabel, 3, 50)

        # ip Textbox
        self.ipBox = Gtk.Entry()
        self.ipBox.get_style_context().add_class("ip-input")
        self.ipBox.set_size_request(250,60)
        fixed.put(self.ipBox, 160, 50)


        # Create Button
        button = Gtk.Button(label="Click me Bro!")
        button.set_size_request(50,50)
        button.connect("clicked", self.on_button_clicked)
        fixed.put(button, 50, 50)

        self.show_all()

    def on_button_clicked(self, widget):
        nm = self.ipBox.get_text()
        os.environ['LD_LIBRARY_PATH'] = './'
        p = subprocess.Popen(['./program', str(nm)], stdout=subprocess.PIPE)
        out, err = p.communicate()
        print(out.decode())

def main():
    win = bufferGUI()
    Gtk.main()

if __name__ == "__main__":
    main()