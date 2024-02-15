import { Injectable } from '@angular/core';
import { Http } from '@angular/http';

import { Trip } from '../models/trip';

@Injectable()
export class TripDataService {

  constructor(private http: Http) { }

  private apiBaseUrl = 'http://localhost:3000/api/';
  private tripUrl = `${this.apiBaseUrl}trips/`;

  public addTrip(formData: Trip): Promise<Trip> {
    console.log('Inside TripDataService#addTrip');
    return this.http
      .post(this.tripUrl, formData) //pass form data in request body
      .toPromise()
      .then(response => response.json() as Trip[])
      .catch(this.handleError);
  }

  public async getTrips(): Promise<Trip[]> {
    console.log('Inside TripDataService#getTrips');
    try {
      const response = await this.http
        .get(`${this.apiBaseUrl}trips`)
        .toPromise();
      return response.json() as Trip[];
    } catch (error) {
      return this.handleError(error);
    }
  }
  private handleError(error: any): Promise<any> {
    console.error('Something has gone wrong', error); //for demo purposes only
    return Promise.reject(error.message || error);
  }
}
