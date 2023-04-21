import gi, subprocess, os

gi.require_version('Gtk', '3.0')
gi.require_version('Vte', '2.91')
from gi.repository import Gtk, Gdk, GLib, Vte

lib_path = os.path.abspath("../src")
os.environ["LD_LIBRARY_PATH"] = f"{os.getenv('LD_LIBRARY_PATH', '')}:{lib_path}"


class bufferGUI(Gtk.Window):
    def errorMsg(titleMsg, errorHeader):
        errorDialog = Gtk.MessageDialog(
            transient_for=None,
            flags=0,
            message_type=Gtk.MessageType.ERROR,
            buttons=Gtk.ButtonsType.OK,
            text=errorHeader
        )
        errorDialog.format_secondary_text(titleMsg)
        errorDialog.run()
        errorDialog.destroy()

    def __init__(self):
        Gtk.Window.__init__(self, title="0x0MDX")
        self.set_default_size(580, 400)
        self.set_resizable(False)
        self.connect("destroy", Gtk.main_quit)
        self.loopOption = "y"

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
        fixed.put(self.author, 400, 5)

        # Main Label
        self.mLabel = Gtk.Label()
        self.mLabel.set_markup("<b> 0x0MemDestruX - 0x0MDX </b>")
        self.mLabel.get_style_context().add_class("mainHeader")
        fixed.put(self.mLabel, 20, 50)

        # IP Label
        self.ipLabel = Gtk.Label(label="IP ADDRESS")
        self.ipLabel.get_style_context().add_class("labels")
        fixed.put(self.ipLabel, 100, 110)

        self.ipBox = Gtk.Entry()
        self.ipBox.set_max_length(16)
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
        fixed.put(finButton, 223, 340)

        # Loop Label
        self.loopLabel = Gtk.Label(label="LOOP")
        self.loopLabel.get_style_context().add_class("labels")
        fixed.put(self.loopLabel, 100, 280)

        self.yesRadio = Gtk.RadioButton.new_with_label_from_widget(None, "Yes")
        self.yesRadio.connect("toggled", self.on_radio_toggled, "y")
        fixed.put(self.yesRadio, 96, 302)

        self.noRadio = Gtk.RadioButton.new_with_label_from_widget(self.yesRadio, "No")
        self.noRadio.connect("toggled", self.on_radio_toggled, "n")
        fixed.put(self.noRadio, 96, 325)

        # IP Address Result Label
        self.ipAddress = Gtk.Label(label="IP ADDRESS: ")
        self.ipAddress.get_style_context().add_class("topSmallLabels")
        fixed.put(self.ipAddress, 5, 380)

        # Port Result Label
        self.resultPortLabel = Gtk.Label(label="PORT: ")
        self.resultPortLabel.get_style_context().add_class("topSmallLabels")
        fixed.put(self.resultPortLabel, 5, 400)

        # Result Buffer Size Label
        self.bufferSizeLabel = Gtk.Label(label="Buffer Size: ")
        self.bufferSizeLabel.get_style_context().add_class("bottomSmallLabels")
        fixed.put(self.bufferSizeLabel, 400, 370)

        self.show_all()

    def on_radio_toggled(self, button, name):
        if name == "y":
            self.loopOption = "y"
        else:
            self.loopOption = "n"

    def on_button_clicked(self, widget):
        ipAddress = self.ipBox.get_text()
        portNo = self.portBox.get_text()
        bufferSize = self.bufferSizeText.get_text()
        vulnName = self.vuln.get_text()

        # Check for Ip Address Input
        if len(ipAddress) >= 14:
            bufferGUI.errorMsg("IP Address Input cannot be more than 14 characters!", "ERROR")
            return False
        elif len(ipAddress) == 0:
            bufferGUI.errorMsg("Please Enter the IP ADDRESS!", "ERROR")
            return False
        else:
            self.ipAddress.set_text("IP ADDRESS: " + ipAddress)
            print("SET IP ADRESS: " + str(ipAddress))

        # Check for Port Input
        if len(portNo) >= 10:
            bufferGUI.errorMsg("Port Input cannot be more than 10 characters!", "ERROR")
            return False
        elif len(portNo) == 0:
            bufferGUI.errorMsg("Please Enter the Port Number!", "ERROR")
            return False
        else:
            self.resultPortLabel.set_text("PORT: " + portNo)
            print("SET PORT: " + portNo)

        print("VULN Name: " + vulnName)

        # Check for Buffer Size Input
        if len(bufferSize) == 0:
            bufferGUI.errorMsg("Please Enter the Buffer Size!", "ERROR")
            return False
        else:
            print("Buffer Size: " + bufferSize)

        p = subprocess.Popen(['../src/program', str(ipAddress), str(portNo), str(bufferSize), str(self.loopOption), str(vulnName)], stdout=subprocess.PIPE)
        out, err = p.communicate()
        buffer_size_str = out.decode().strip()
        self.bufferSizeLabel.set_text("Buffer Size: " + buffer_size_str)
        if self.loopOption == "y":
            print("Loop Option: YES")
        else:
            print("Loop Option: NO")


win = bufferGUI()
win.connect("destroy", Gtk.main_quit)
win.show_all()
Gtk.main()