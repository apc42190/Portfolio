import kivy
from kivy.app import App
from kivy.core.clipboard import Clipboard
from kivy.uix.boxlayout import BoxLayout
from kivy.properties import StringProperty
from kivy.properties import BooleanProperty
from kivy.config import Config

import secrets


kivy.require("1.9.0")


#Lists of characters to be used for password generation
symbols = ['@', '#', '$', '%']
numbers = [x for x in range(10)]
letters = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']



class MainPage(BoxLayout):
    number_toggle_state = False                                         #Keeps track of if numbers are desired
    symbol_toggle_state = False                                         #Keeps track of if symbols are desired
    capital_toggle_state = False                                        #Keeps track of if capital letters are desired
    slider_value = 8                                                    #Tracks desired character count from slider
    generated_password = StringProperty("") 
    password_button_text = StringProperty("Press above to generate") 
    password_generated = BooleanProperty(True)                           

    def toggle_button_state(self, widget):
        '''Changes text on toggle buttons from "On" to "Off" and back'''
        if widget.state == "normal":
            widget.text = "No"
        else:
            widget.text = "Yes"

    def toggle_number_state(self, widget):
        '''Modifies number_toggle_state on button press'''
        self.toggle_button_state(widget)
        self.number_toggle_state = not self.number_toggle_state

    def toggle_symbol_state(self, widget):
        '''Modifies symbol_toggle_state on button press'''
        self.toggle_button_state(widget)
        self.symbol_toggle_state = not self.symbol_toggle_state

    def toggle_capital_state(self, widget):
        '''Modifies capital_toggle_state on button press'''
        self.toggle_button_state(widget)
        self.capital_toggle_state = not self.capital_toggle_state

    def set_slider_value(self, widget):
        '''Updates slider value variable when slider is moved'''
        self.slider_value = int(widget.value)

    def generate_password(self):
        '''Generates password based on toggle buttons and slider'''
        self.password_generated = False
        while True:                                         #loops till password contains all necessary elements
            self.generated_password = ""
            option_list = list(letters)
            if self.number_toggle_state == True:                     #Adds numbers to list if required
                option_list.extend(numbers)
            if self.symbol_toggle_state == True:                     #Adds symbols to list if required
                option_list.extend(symbols)
            if self.capital_toggle_state == True:                    #Adds capital letters to list if required
                option_list.extend([x.upper() for x in letters])
            
            #Loops the desired number of characters and generates password 
            for i in range(self.slider_value):
                self.generated_password += str(secrets.choice(option_list))  
            

            #Checks if password contains all required elements. If not it starts again. 
            if self.number_toggle_state == True:
                if set([str(x) for x in numbers]).isdisjoint(set(self.generated_password)):
                    continue
            if self.symbol_toggle_state == True:
                if set(symbols).isdisjoint(set(self.generated_password)):
                    continue
            if self.capital_toggle_state == True:
                if set([x.upper() for x in letters]).isdisjoint(set(self.generated_password)):
                    continue
            break
        self.password_button_text = f"Password: {self.generated_password}"

    def copy_password(self):
        Clipboard.copy(self.generated_password)
        self.password_button_text = "Copied!"



class PasswordGeneratorApp(App):
    pass

PasswordGeneratorApp().run()