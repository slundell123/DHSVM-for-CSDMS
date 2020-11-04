#import pymt
#from pymt.models import Waves

from pymt import plugins
cem = plugins.Cem()

model = Waves()
cfg_file, cfg_dir = model.setup()

print(cfg_file, cfg_dir)

args = model.setup()

cfg_dir = '.'

model.setup(cfg_dir)

for name, value in model.parameters:
    print(name, '=', value)

model.setup(cfg_dir, incoming_wave_height=3.5)
print()
for name, value in model.parameters:
    print(name, '=', value)

print("-----------------------")

waves = Waves()
config = waves.setup()
waves.initialize(*config)
print(waves.start_time)
print(waves.end_time)
print(waves.time)
print(waves.time_units)
print(waves.time_step)
print(waves.time)
waves.update()
print(waves.time)

print(waves.input_var_names)


print(waves.output_var_names)

print(waves.get_value('sea_surface_water_wave__height'))


waves.set_value('sea_surface_water_wave__height', 3.5)

print(waves.get_value('sea_surface_water_wave__height'))

waves.finalize()

