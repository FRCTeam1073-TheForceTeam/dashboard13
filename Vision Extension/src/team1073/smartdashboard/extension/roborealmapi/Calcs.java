/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.roborealmapi;

/**
 *
 * @author Michael
 */
import java.util.ArrayList;

public class Calcs {

	public ArrayList<Double> X, Y;
	// private int k;
	// private static double[][] points;
	private static double x;
	// The x position of the frisbee.
	private static double y;
	// The y position of the frisbee.
	private static double vx;
	// The x velocity of the frisbee.
	private static double vy;
	// The y velocity of the frisbee.
	private static final double g = -9.81;
	// The acceleration of gravity (m/s^2).
	private static final double m = 0.180;
	// The mass of a standard frisbee in kilograms.
	private static final double RHO = 1.23;
	// The density of air in kg/m^3.
	private static final double AREA = 0.061311;
	// The area of a standard frisbee.
	private static final double CL0 = 0.1;
	// The lift coefficient at alpha = 0.
	private static final double CLA = 1.4;
	// The lift coefficient dependent on alpha.
	private static final double CD0 = 0.08;
	// The drag coefficent at alpha = 0.
	private static final double CDA = 2.72;
	// The drag coefficient dependent on alpha.
	private static final double ALPHA0 = -4;
	
	public double getHeight(double distance, double velocity, double theta, double initalHeight) {
		velocity = velocity * 6 * 2.54 * Math.PI / (2 * 60 * 100);
		double y0 = initalHeight/39.37;
		double vx0 = velocity * Math.cos(theta * Math.PI / 180);
		double vy0 = velocity * Math.sin(theta * (Math.PI) / 180);
		double alpha = theta;
		double deltaT = .005;
		// Calculation of the lift coefficient using the relationship given
		// by S. A. Hummel.
		double cl = CL0 + CLA * alpha * Math.PI / 180;
		// Calculation of the drag coefficient (for Prantl’s relationship)
		// using the relationship given by S. A. Hummel.
		double cd = CD0 + CDA * Math.pow((alpha - ALPHA0) * Math.PI / 180, 2);
		// Initial position x = 0.
		x = 0;
		// Initial position y = y0.
		y = y0;
		// Initial x velocity vx = vx0.
		vx = vx0;
		// Initial y velocity vy = vy0.
		vy = vy0;
		
			// A while loop that performs iterations until the y position
			// reaches zero (i.e. the frisbee hits the ground).
			while (y > 0) {
				// The change in velocity in the y direction obtained setting
				// the
				// net force equal to the sum of the gravitational force and the
				// lift force and solving for delta v.
				double deltavy = (RHO * Math.pow(vx, 2) * AREA * cl / 2 / m + g)
						* deltaT;
				// The change in velocity in the x direction, obtained by
				// solving the force equation for delta v. (The only force
				// present is the drag force).
				double deltavx = -RHO * Math.pow(vx, 2) * AREA * cd * deltaT;
				// The new positions and velocities are calculated using
				// simple introductory mechanics.
				vx = vx + deltavx;
				vy = vy + deltavy;
				x = x + vx * deltaT;
				y = y + vy * deltaT;

				if(x >= distance) {
					return y;
                                }
			}
		return 0;
	}
}
