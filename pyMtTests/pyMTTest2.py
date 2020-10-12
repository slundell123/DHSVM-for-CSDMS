import pymt
from pymt.models import Cem, Waves

waves = Waves()
cem = Cem()

waves.initialize(*waves.setup())
cem.initialize(*cem.setup())
print(waves.output_var_names)
print(cem.input_var_names)
for time in range(1000):
    waves.update()
    angle = waves.get_value("sea_surface_water_wave__azimuth_angle_of_opposite_of_phase_velocity")
    cem.set_value("sea_surface_water_wave__azimuth_angle_of_opposite_of_phase_velocity", angle)
    cem.update()