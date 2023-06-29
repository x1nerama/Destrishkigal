import json
from flask import Flask, render_template, request

app = Flask(__name__)
ip = None

@app.route('/', methods=['POST', 'GET'])
def send_variable():
    global ip, port, loop_counter, payload
    if request.method == 'POST':
        ip = request.form.get('ipAddress')
        port = request.form.get('port')
        loop_counter = request.form.get('loop_counter')
        payload = request.form.get('payload')
        save_to_json(ip, port, loop_counter, payload)
        return render_template('index.html')
    else:
        return('This is a get requests')
def save_to_json(ip, port, loop_counter, payload):
    data = [
            {'ip': ip},
            {'port': port},
            {'loop_counter': loop_counter},
            {'payload': payload} 
           ]
    with open('../src/data.json', 'w') as json_file:
        json.dump(data, json_file)

if __name__ == '__main__':
    app.run(debug=True)
