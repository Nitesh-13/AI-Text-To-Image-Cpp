#include "request.h"
using namespace std;


int main() {

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