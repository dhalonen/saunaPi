//
//  ContentView.swift
//  saunaPiPhone
//
//  Created by David Halonen on 3/12/21.
//

import SwiftUI

struct ContentView: View {
    @StateObject var saunaEnvironment = SaunaEnvironment()
    var body: some View {
        ZStack {
            ReportBlockContainer()
            //Put a transparent text view over everything. This receives taps for updates.
            Text("")
                .frame(maxWidth: .infinity, maxHeight: .infinity)
                .background(Color(.systemBackground))
                .opacity(0.01)
                .onTapGesture {
                    getSaunaData(saunaEnvironment)
                }
        }
        .background(Color(.systemBackground))
        .environmentObject(saunaEnvironment)
    }
}

private func urlToSaunaData() -> String {
    if let key = UserDefaults.standard.string(forKey: "dataUrl"){
        return key
    }
    return "http://saunapi.harmon/data.json"
}

func getSaunaData(_ saunaEnvironment: SaunaEnvironment) {
    let url = URL(string: urlToSaunaData())!

    //TODO convert this to async
    let task = URLSession.shared.dataTask(with: url) {(data, response, error) in
        guard let data = data else { return }
        print(String(data: data, encoding: .utf8)!)
        
        let decoder = JSONDecoder()
        do {
            let saunaEnvironmentData = try decoder.decode(SaunaEnvironmentData.self, from: data)
            print(saunaEnvironmentData)
            //We are on a background thread. Need to perform environment object update on main.
            DispatchQueue.main.async {
                saunaEnvironment.temperature = saunaEnvironmentData.temperature
                saunaEnvironment.timeStamp = saunaEnvironmentData.timeStamp
            }
        } catch {
            print(error)
        }
    }
    task.resume()
}

struct SaunaEnvironmentData: Codable {
    var temperature: Int
    var timeStamp: String
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView().preferredColorScheme(/*@START_MENU_TOKEN@*/.dark/*@END_MENU_TOKEN@*/)
    }
}
