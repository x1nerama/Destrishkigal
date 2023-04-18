import gi, subprocess, os
gi.require_version('Gtk', '3.0')
gi.require_version('Vte', '2.91')
from gi.repository import Gtk, Gdk, GLib, Vte
lib_path = os.path.abspath("../src")
os.environ["LD_LIBRARY_PATH"] = f"{os.getenv('LD_LIBRARY_PATH', '')}:{lib_path}"
class bufferGUI(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title="Bufferoverflow GUI")
        self.set_default_size(580, 380)
        self.set_resizable(False)
        self.connect("destroy", Gtk.main_quit)

        # Enable CSS Provider
        cssProvider = Gtk.CssProvider()
        cssProvider.load_from_path("utils/css/style.css")
        screen = Gdk.Screen.get_default()
        styleContext = self.get_style_context()
        styleContext.add_provider_for_screen(screen, cssProvider, Gtk.STYLE_PROVIDER_PRIORITY_USER)

        # Get Style Context
        styleContext = self.get_style_context()
        styleContext.add_provider(cssProvider, Gtk.STYLE_PROVIDER_PRIORITY_USER)

        # Set background color using CSS
        styleContext.add_class("bg-color")

        # Create Fixed
        fixed = Gtk.Fixed()
        self.add(fixed)

        # Author Label
        self.author = Gtk.Label(label="github.com/devtbenoth")
        self.author.get_style_context().add_class("labels")
        fixed.put(self.author, 5, 380)

        # Main Label
        self.mLabel = Gtk.Label()
        self.mLabel.set_markup("<b> BUFFEROVERFLOW GUI </b>")
        self.mLabel.get_style_context().add_class("mainHeader")
        fixed.put(self.mLabel, 50, 50)

        # IP Label
        self.ipLabel = Gtk.Label(label="IP ADDRESS")
        self.ipLabel.get_style_context().add_class("labels")
        fixed.put(self.ipLabel, 100, 110)

        # ip Textbox
        self.ipBox = Gtk.Entry()
        self.ipBox.get_style_context().add_class("inputs")
        self.ipBox.set_size_request(200, 1)
        fixed.put(self.ipBox, 50, 140)

        # PORT Label
        self.portLabel = Gtk.Label(label="PORT")
        self.portLabel.get_style_context().add_class("labels")
        fixed.put(self.portLabel, 378, 110)

        # PORT Textbox
        self.portBox = Gtk.Entry()
        self.portBox.get_style_context().add_class("inputs")
        self.portBox.set_size_request(200, 1)
        fixed.put(self.portBox, 300, 140)
        
        # vulnName label
        self.vulnLabel = Gtk.Label(label="VULN NAME (Optional)")
        self.vulnLabel.get_style_context().add_class("labels")
        fixed.put(self.vulnLabel, 68, 195)

        # vulnName Textbox
        self.vuln = Gtk.Entry()
        self.vuln.get_style_context().add_class("inputs")
        self.vuln.set_size_request(200, 1)
        fixed.put(self.vuln, 50, 225)

        # bufferSize label
        self.bufferSizeLabel = Gtk.Label(label="Buffer Size")
        self.bufferSizeLabel.get_style_context().add_class("labels")
        fixed.put(self.bufferSizeLabel, 358, 195)

        # bufferSize Textbox
        self.bufferSizeText = Gtk.Entry()
        self.bufferSizeText.get_style_context().add_class("inputs")
        self.bufferSizeText.set_size_request(200, 1)
        fixed.put(self.bufferSizeText, 300, 225)

        # Finish Button
        finButton = Gtk.Button(label="GO BUFF!")
        finButton.get_style_context().add_class("finish-button")
        finButton.connect("clicked", self.on_button_clicked)
        finButton.set_size_request(110, 40)
        fixed.put(finButton, 223, 280)

        # create the terminal widget
        terminal = Vte.Terminal()

        # set the size of the terminal widget
        terminal.set_size(800, 600)

        # create a box to hold the terminal widget
        box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL)
        box.pack_end(terminal, True, True, 0)

        # add the box to the window
        self.add(box)

        # position the terminal widget at the bottom of the window
        self.set_size_request(800, 800)
        self.set_position(Gtk.WindowPosition.CENTER)
        self.set_resizable(True)
        self.connect("destroy", Gtk.main_quit)

        # launch a terminal program inside the widget
        pid, _, _ = GLib.spawn_async(
            ["/bin/bash"],
            flags=GLib.SpawnFlags.DO_NOT_REAP_CHILD,
            standard_output=None,
            standard_error=None,
        )
        terminal.set_pty(Vte.Pty.new_foreign_sync(pid))
        self.show_all()
    def on_button_clicked(self, widget):
        ipAddress = self.ipBox.get_text()
        portNo = self.portBox.get_text()
        vulnName = self.vuln.get_text()
        bufferSize = self.bufferSizeText.get_text()
        p = subprocess.Popen(['../src/program', str(ipAddress), str(portNo), str(bufferSize), str(vulnName)], stdout=subprocess.PIPE)
        out, err = p.communicate()
        print(out.decode())

def main():
    win = bufferGUI()
    Gtk.main()

if __name__ == "__main__":
    main()