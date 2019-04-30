<?xml version="1.0" encoding="utf-8"?>
<fx:flux-document xmlns:fx="http://www.bosch.com/Flux/Model" xmlns:b="http://www.bosch.com/Flux/Model/Base" xmlns:tv="http://www.bosch.com/Flux/Model/Base/TaggedValues" xmlns:types="http://www.bosch.com/Flux/Model/Base/Types" xmlns:statistics="http://www.bosch.com/Flux/Model/Base/Statistics" xmlns:cmp="http://www.bosch.com/Flux/Model/Components" xmlns:cs="http://www.bosch.com/Flux/Model/Constraints" xmlns:dsc="http://www.bosch.com/Flux/Model/Descriptions" xmlns:cnt="http://www.bosch.com/Flux/Model/Descriptions/Content" xmlns:dd="http://www.bosch.com/Flux/Model/DetailedDesign" xmlns:doc="http://www.bosch.com/Flux/Model/Document" xmlns:ev="http://www.bosch.com/Flux/Model/Events" xmlns:hw="http://www.bosch.com/Flux/Model/Hardware" xmlns:imp="http://www.bosch.com/Flux/Model/Implementations" xmlns:map="http://www.bosch.com/Flux/Model/Mapping" xmlns:middle="http://www.bosch.com/Flux/Model/MiddleWare" xmlns:os="http://www.bosch.com/Flux/Model/OperatingSystems" xmlns:req="http://www.bosch.com/Flux/Model/Requirements" xmlns:sw="http://www.bosch.com/Flux/Model/Software" xmlns:gph="http://www.bosch.com/Flux/Model/Software/Graph" xmlns:hsm="http://www.bosch.com/Flux/Model/Software/HSM" xmlns:lab="http://www.bosch.com/Flux/Model/Software/Labels" xmlns:prc="http://www.bosch.com/Flux/Model/Software/Processes" xmlns:expr="http://www.bosch.com/Flux/Model/Software/Expressions" xmlns:stm="http://www.bosch.com/Flux/Model/Stimuli" xmlns:u="http://www.bosch.com/Flux/Model/Units" xmlns:val="http://www.bosch.com/Flux/Model/Validation" xmlns:var="http://www.bosch.com/Flux/Model/Variations" version="0.9">
  <requirements-model />
  <variations-model>
    <variation-points>
      <variation-point name="nrc2/if/iwd/build">
        <variations>
          <variation name="hw" />
          <variation name="utf" />
        </variations>
      </variation-point>
      <variation-point name="nrc2/if/iwd/build_type">
        <variations>
          <variation name="debug" />
          <variation name="release" />
        </variations>
      </variation-point>
      <variation-point name="nrc2/if/iwd/arch">
        <variations>
          <variation name="x86" />
        </variations>
      </variation-point>
      <variation-point name="nrc2/if/iwd/platform">
        <variations>
          <variation name="base" />
          <variation name="plus" />
        </variations>
      </variation-point>
    </variation-points>
  </variations-model>
</fx:flux-document>