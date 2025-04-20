import sys
import requests as r
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QLineEdit, QPushButton, QVBoxLayout
from PyQt5.QtCore import Qt


class WeatherApp(QWidget):
    def __init__(self):
        super().__init__()
        self.city_label = QLabel("Enter City Name", self)
        self.city_input = QLineEdit(self)
        self.get_weather_button = QPushButton("Get Weather", self)
        self.temperature_label = QLabel("30°C", self)
        self.emoji_label = QLabel("☀️", self)
        self.description_label = QLabel("Sunny", self)
        self.initUI()

    def initUI(self):
        self.setWindowTitle("Weather App")
        vbox = QVBoxLayout()
        vbox.addWidget(self.city_label)
        vbox.addWidget(self.city_input)
        vbox.addWidget(self.get_weather_button)
        vbox.addWidget(self.temperature_label)
        vbox.addWidget(self.emoji_label)
        vbox.addWidget(self.description_label)

        self.setLayout(vbox)

        self.city_label.setAlignment(Qt.AlignCenter)
        self.city_input.setAlignment(Qt.AlignCenter)
        self.temperature_label.setAlignment(Qt.AlignCenter)
        self.emoji_label.setAlignment(Qt.AlignCenter)
        self.description_label.setAlignment(Qt.AlignCenter)

        self.city_label.setObjectName("city_label")
        self.city_input.setObjectName("city_input")
        self.temperature_label.setObjectName("temperature_label")
        self.emoji_label.setObjectName("emoji_label")
        self.description_label.setObjectName("description_label")
        self.get_weather_button.setObjectName("get_weather_button")

        self.setStyleSheet("""
                QWidget {
                    background-color: #f0f8ff;
                    border-radius: 10px;
                    padding: 20px;
                }

                QLabel, QLineEdit, QPushButton {
                    font-family: 'Segoe UI', sans-serif;
                    color: #333;
                }

                QLabel#city_label {
                    font-size: 36px;
                    font-weight: bold;
                    color: #2e8b57;
                }

                QLineEdit#city_input {
                    font-size: 30px;
                    padding: 10px;
                    border-radius: 15px;
                    border: 2px solid #2e8b57;
                    background-color: #fff;
                }

                QPushButton#get_weather_button {
                    font-size: 24px;
                    font-weight: bold;
                    background-color: #2e8b57;
                    color: white;
                    padding: 12px;
                    border-radius: 15px;
                    border: none;
                }

                QPushButton#get_weather_button:hover {
                    background-color: #3cb371;
                }

                QLabel#temperature_label {
                    font-size: 75px;
                    color: #ff6347;
                    font-weight: bold;
                }

                QLabel#emoji_label {
                    font-size: 100px;
                    font-family: 'Segoe UI Emoji', sans-serif;
                }

                QLabel#description_label {
                    font-size: 40px;
                    color: #4682b4;
                    font-weight: bold;
                }

                QVBoxLayout {
                    spacing: 20px;
                }
                """)

        # Connect the button click to the get_weather function
        self.get_weather_button.clicked.connect(self.get_weather)

    def get_weather(self):
        api_key = "5a92643be12a43e6dcd4d8313ceb028c"
        city = self.city_input.text()
        url = f"https://api.openweathermap.org/data/2.5/weather?q={city}&appid={api_key}"
        response = r.get(url)
        data = response.json()

        # Handle successful response
        if response.status_code == 200:
            main = data['main']
            weather = data['weather'][0]

            # Update the UI with the weather data
            temperature = main['temp'] - 273.15  # Convert from Kelvin to Celsius
            self.temperature_label.setText(f"{temperature:.2f}°C")
            self.description_label.setText(weather['description'].capitalize())

            # Update emoji based on weather condition
            if 'clear' in weather['main'].lower():
                self.emoji_label.setText("☀️")
            elif 'cloud' in weather['main'].lower():
                self.emoji_label.setText("☁️")
            elif 'rain' in weather['main'].lower():
                self.emoji_label.setText("🌧️")
            else:
                self.emoji_label.setText("🌈")
        else:
            self.temperature_label.setText("Error")
            self.emoji_label.setText("❌")
            self.description_label.setText("City not found")


if __name__ == '__main__':
    app = QApplication(sys.argv)
    weather_app = WeatherApp()
    weather_app.show()
    sys.exit(app.exec_())
