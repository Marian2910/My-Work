import toastr, { success, error} from "toastr";


export function updateOrder(orderId, newType, newQuantity) {
    return fetch(`https://localhost:7163/api/Order/Patch`, {
      method: `PATCH`,
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify({
        orderId: orderId,
        ticketCategory: newType,
        numberOfTickets: +newQuantity,
      })
    }).then((res) => {
      if (res.status === 200) {
        toastr.success('Comanda a fost modificata cu succes!');
      } else {
        toastr.error('Eroare la modificarea comenzii!');
      }
      return res;
    }).catch((err) => {
      throw new Error(err);
    });
  }
  