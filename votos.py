class VotingSystem:
    def __init__(self):
        self.voters = {}  
        self.votes = {}   

    def vote(self, voter_id, candidate):
        if voter_id in self.voters:
            return "Erro: Eleitor já votou."
        
        self.voters[voter_id] = True  
        if candidate in self.votes:
            self.votes[candidate] += 1  
        else:
            self.votes[candidate] = 1 

        return f"Voto registrado para {candidate}!"

class Results:
    def __init__(self, votes):
        self.votes = votes

    def show_results(self):
        print("Resultados da eleição:")
        for candidate, count in self.votes.items():
            print(f"{candidate}: {count} votos")

def main():
    voting_system = VotingSystem()

    while True:
        print("\nMenu:")
        print("1 - Votar")
        print("2 - Mostrar resultados")
        print("0 - Sair")
        
        choice = input("Escolha uma opção: ")

        if choice == '1':
            voter_id = input("Digite seu ID (ex: CPF ou número de registro): ")
            candidate = input("Digite o nome do candidato: ")
            print(voting_system.vote(voter_id, candidate))
        
        elif choice == '2':
            results = Results(voting_system.votes)
            results.show_results()
        
        elif choice == '0':
            print("Saindo...")
            break
        
        else:
            print("Opção inválida! Tente novamente.")

if __name__ == "__main__":
    main()
