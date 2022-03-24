#include "request.h"
using namespace std;

void print_introduction();

int main() {

    print_introduction();

    string apiUrl = "https://api-inference.huggingface.co/models/runwayml/stable-diffusion-v1-5";
    string authToken = "XXXXXXXXXXXXXXXXXXXX"; //Hugging Face Token
    string responseData, query;

    cout<<"Enter a query: ";
    getline(cin,query);

    string payload = "{\"inputs\": \""+query+"\"}";

    if (req.post(apiUrl, payload, responseData, authToken)) {
        ofstream imageFile("output.jpg", ios::binary);
        if (imageFile) {
            imageFile.write(responseData.c_str(), responseData.size());
            imageFile.close();
            cout << "Image downloaded successfully as output.jpg"<< endl;
        } else {
            cerr << "Failed to create output image file." << endl;
        }
    } else {
        cerr << "POST request failed." << endl;
    }

    return 0;
}

void print_introduction(){
    string asciiArt =
        "          _____   _______        _     _______      _____ __  __  _____ \n"
        "    /\\   |_   _| |__   __|      | |   |__   __|    |_   _|  \\/  |/ ____|\n"
        "   /  \\    | |      | | _____  _| |_     | | ___     | | | \\  / | |  __ \n"
        "  / /\\ \\   | |      | |/ _ \\ \\/ / __|    | |/ _ \\    | | | |\\/| | | |_ |\n"
        " / ____ \\ _| |_     | |  __/>  <| |_     | | (_) |  _| |_| |  | | |__| |\n"
        "/_/    \\_\\_____|    |_|\\___/_/\\_\\__|     |_|\\___/  |_____|_|  |_|\\_____|\n\n";
    cout<<asciiArt;
    cout<<"- Enter a query thats suits your image discription.\n- Program will call the api for image generation\n- The Image will be saved in the same directory as the program\n\n==] Author - Nitesh [==\n\n";

}